on_tableWidget_profiles_itemSelectionChanged()
{
	QTableWidget *profilesWidget = this->ui->tableWidget_profiles;
	if (profilesWidget->selectedItems().size() == 0) {
		return;
	}

	QString pluginName;
	int row = this->ui->listWidget_plugins->currentRow();
	pluginName = this->ui->listWidget_plugins->item(row)->text();


	AB_IMEXPORTER *ie = AB_Banking_GetImExporter(banking->getAqBanking(),
						     pluginName.toUtf8());

	bool enabled;
	enabled = (AB_ImExporter_GetFlags(ie) & AB_IMEXPORTER_FLAGS_GETPROFILEEDITOR_SUPPORTED);

	this->ui->actionNewProfile->setEnabled(enabled);
	this->ui->actionEditProfile->setEnabled(enabled);

	row = profilesWidget->selectedItems().at(0)->row();
	if (profilesWidget->item(row, 4) != NULL) {

		enabled = profilesWidget->item(row, 4)->checkState() == Qt::Unchecked;
	} else {
		enabled = false;
	}
	this->ui->actionDeleteProfile->setEnabled(enabled);


	if (profilesWidget->item(row, 0) != NULL) {
		QString profileName = profilesWidget->item(row, 0)->text();
		this->selection.insert(pluginName, profileName);
	}
}
