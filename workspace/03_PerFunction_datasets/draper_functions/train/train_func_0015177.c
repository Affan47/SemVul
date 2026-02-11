ok()
{
	double weight;
	QString tmp=weightLineEdit->text();
	weight_sscanf(tmp, "%lf", &weight);
	if(weight<100.0 || weight>100.0){
		QMessageBox::warning(this, tr("FET information"),
			tr("Invalid weight (percentage). It has to be 100"));
		return;
	}

	this->_ctr->weightPercentage=weight;
	this->_ctr->minGapsBetweenBuildingChanges=minGapsSpinBox->value();

	gt.rules.internalStructureComputed=false;
	setRulesModifiedAndOtherThings(&gt.rules);

	this->close();
}
