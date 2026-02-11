addFileSlot()
{
    QStringList files = QFileDialog::getOpenFileNames(this, QString(), QDir::homePath());
    bool emptyList = files.isEmpty();

    ui->startButton->setEnabled(!emptyList || ui->filesListWidget->count());

    if (emptyList)
        return;

    for (int i = 0; i < files.size(); i++) {
        ui->filesListWidget->addItem(files.at(i));
    }
}
