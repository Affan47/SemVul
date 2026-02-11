on_toolButton_selectAccountData_clicked()
{
	QString file = QFileDialog::getSaveFileName(this,
						    tr("Aktuelle Daten Speichern in ..."),
						    this->ui->lineEdit_dataDir->text(),
						    tr("Context-Dateien (*.ctx);;Alle Dateien (*.*)"),
						    NULL,
						    QFileDialog::DontConfirmOverwrite);

	if (!file.isEmpty() || QFile::exists(file)) {
		this->ui->lineEdit_accountData->setText(file);
	}
}
