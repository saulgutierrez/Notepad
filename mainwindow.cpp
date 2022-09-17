#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->plainTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbrir_triggered()
{
    QFile archivo;
    QTextStream io;
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this, "Abrir");
    if(nombreArchivo.isEmpty()) {
        return;
    }
    archivo.setFileName(nombreArchivo);
    archivo.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!archivo.isOpen()) {
        QMessageBox::critical(this, "Error", archivo.errorString());
        return;
    }
    io.setDevice(&archivo);
    ui->plainTextEdit->setPlainText(io.readAll());
    archivo.close();
}


void MainWindow::on_actionGuardar_como_triggered()
{
    QFile arch;
    QTextStream io;
    QString nombreArch;
    nombreArch = QFileDialog::getSaveFileName(this, "Guardar");
    if(nombreArch.isEmpty()) {
        return;
    }
    arch.setFileName(nombreArch);
    arch.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!arch.isOpen()) {
        QMessageBox::critical(this, "Error", arch.errorString());
        return;
    }
    io.setDevice(&arch);
    io << ui->plainTextEdit->toPlainText();
    arch.flush();
    arch.close();
}


void MainWindow::on_actionQuitar_triggered()
{
    close();
}


void MainWindow::on_actionCopiar_triggered()
{
    ui->plainTextEdit->copy();
}


void MainWindow::on_actionCortar_triggered()
{
    ui->plainTextEdit->cut();
}


void MainWindow::on_actionPegar_triggered()
{
    ui->plainTextEdit->paste();
}


void MainWindow::on_actionAcerca_de_triggered()
{
    QString txt;
    txt  = "Autor: Saúl Gutiérrez\n";
    txt += "Fecha: 16/Septiembre/2022\n";
    txt += "Software: (C) Notepad (R)";

    QMessageBox::about(this, "Notepad", txt);
}


void MainWindow::on_actionAcerca_de_Qt_triggered()
{
    QMessageBox::aboutQt(this, "Qt");
}

