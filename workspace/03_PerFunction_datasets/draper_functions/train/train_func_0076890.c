start(){
	if(!gt.rules.internalStructureComputed){
		if(!gt.rules.computeInternalStructure(this)){
			QMessageBox::warning(this, TimetableGenerateForm::tr("FET warning"), TimetableGenerateForm::tr("Data is wrong. Please correct and try again"));
			return;
		}
	}

	if(!gt.rules.initialized || gt.rules.activitiesList.isEmpty()){
		QMessageBox::critical(this, TimetableGenerateForm::tr("FET information"),
			TimetableGenerateForm::tr("You have entered simulation with uninitialized rules or 0 activities...aborting"));
		assert(0);
		exit(1);
		return;
	}

	currentResultsTextEdit->setPlainText(TimetableGenerateForm::tr("Entering simulation....precomputing, please be patient"));

	gen.abortOptimization=false;
	bool ok=gen.precompute(this);

	if(!ok){
		currentResultsTextEdit->setPlainText(TimetableGenerateForm::tr("Cannot generate - please modify your data"));
		currentResultsTextEdit->update();

		QMessageBox::information(this, TimetableGenerateForm::tr("FET information"),
		 TimetableGenerateForm::tr("Your data cannot be processed - please modify it as instructed"));

		return;
	}

	startPushButton->setDisabled(TRUE);
	stopPushButton->setEnabled(TRUE);
	stopHighestPushButton->setEnabled(TRUE);
	closePushButton->setDisabled(TRUE);
	writeResultsPushButton->setEnabled(TRUE);
	writeHighestStagePushButton->setEnabled(TRUE);
	seeImpossiblePushButton->setEnabled(TRUE);
	seeInitialOrderPushButton->setEnabled(TRUE);

	simulation_running=true;

	gen.c.makeUnallocated(gt.rules);

	TimetableExport::writeRandomSeed(this, true);

	generateThread.start();
}
