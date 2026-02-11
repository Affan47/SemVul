ok()
{
	if(!simulation_running)
		gt.rules.setInstitutionName(institutionNameLineEdit->text());
	else{
		QMessageBox::information(this, tr("FET information"),
			tr("Cannot update institution name during simulation\n"
			"Please stop simulation before this"));
		return;
	}

	this->close();
}
