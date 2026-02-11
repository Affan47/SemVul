tapemapClicked()
{
	if (mInternalChange) return;
	mInternalChange = true;

	if (ui.tapemapCheckBox->isChecked())
	{
		ui.allCheckBox->setChecked(false);
		ui.fileInfoCheckBox->setChecked(false);
		ui.labelInfoCheckBox->setChecked(false);
		ui.dataInfoCheckBox->setChecked(false);
		ui.allCheckBox->setEnabled(false);
		ui.fileInfoCheckBox->setEnabled(false);
		ui.labelInfoCheckBox->setEnabled(false);
		ui.dataInfoCheckBox->setEnabled(false);
	}
	else
	{
		ui.allCheckBox->setEnabled(true);
		ui.fileInfoCheckBox->setEnabled(true);
		ui.labelInfoCheckBox->setEnabled(true);
		ui.dataInfoCheckBox->setEnabled(true);
		ui.allCheckBox->setChecked(true);
	}

	mInternalChange = false;
}
