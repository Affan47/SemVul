ok()
{
	double weight;
	QString tmp=weightLineEdit->text();
	weight_sscanf(tmp, "%lf", &weight);
	if(weight<0.0 || weight>100){
		QMessageBox::warning(this, tr("FET information"),
			tr("Invalid weight"));
		return;
	}

	if(selectedRoomsListWidget->count()==0){
		QMessageBox::warning(this, tr("FET information"),
			tr("Empty list of selected rooms"));
		return;
	}
	if(selectedRoomsListWidget->count()==1){
		QMessageBox::warning(this, tr("FET information"),
			tr("Only one selected room - please use constraint subject activity tag preferred room if you want a single room"));
		return;
	}

	if(subjectsComboBox->currentIndex()<0){
		QMessageBox::warning(this, tr("FET information"),
			tr("Invalid selected subject"));
		return;
	}
	QString subject=subjectsComboBox->currentText();

	if(activityTagsComboBox->currentIndex()<0){
		QMessageBox::warning(this, tr("FET information"),
			tr("Invalid selected activity tag"));
		return;
	}
	QString activityTag=activityTagsComboBox->currentText();

	QStringList roomsList;
	for(int i=0; i<selectedRoomsListWidget->count(); i++)
		roomsList.append(selectedRoomsListWidget->item(i)->text());

	this->_ctr->weightPercentage=weight;
	this->_ctr->subjectName=subject;
	this->_ctr->activityTagName=activityTag;
	this->_ctr->roomsNames=roomsList;

	gt.rules.internalStructureComputed=false;
	setRulesModifiedAndOtherThings(&gt.rules);

	this->close();
}
