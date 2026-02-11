openFile(const QString& fileName)
{
	if(simulation_running){
		QMessageBox::information(this, tr("FET information"),
			tr("Allocation in course.\nPlease stop simulation before this."));
		return;
	}

	int confirm=0;

	if(gt.rules.modified){
		switch( QMessageBox::question(
		 this,
		 tr("FET application"),
		 tr("Your current data file has been modified. Are you sure you want to open another data file?"),
		 QMessageBox::Yes|QMessageBox::No
		 ) ){
		case QMessageBox::Yes:
			confirm=1;
			break;
		case QMessageBox::No:
			confirm=0;
			break;
		default:
			assert(0);
			break;
		}
	}
	else
		confirm=1;

	if(confirm){
		QString s=fileName;

		if(s.isNull()){
			s = QFileDialog::getOpenFileName(this, tr("Choose a file to open"),
			 WORKING_DIRECTORY,
			 tr("FET XML files", "Instructions for translators: FET XML is a type of file format (using text mode). "
			 "So this field means files in the FET XML format")+" (*.fet)"+";;"+tr("All files")+" (*)");

			if(s.isNull())
				return;
		}

		int tmp2=s.lastIndexOf(FILE_SEP);
		QString s2=s.right(s.length()-tmp2-1);

		if(s2.indexOf("\"") >= 0){
			QMessageBox::warning(this, tr("FET information"),
			 tr("Please do not use quotation marks \" in filename, the html css code does not work."
			  " File was not loaded. Please rename it, removing not allowed characters and open it after that with FET."));
			return;
		}
		if(s2.indexOf(";") >= 0){
			QMessageBox::warning(this, tr("FET information"),
			 tr("Please do not use semicolon ; in filename, the html css code does not work."
			  " File was not loaded. Please rename it, removing not allowed characters and open it after that with FET."));
			return;
		}
		if(s2.indexOf("#") >= 0){
			QMessageBox::warning(this, tr("FET information"),
			 tr("Please do not use # in filename, the html css code does not work."
			  " File was not loaded. Please rename it, removing not allowed characters and open it after that with FET."));
			return;
		}


		else{


			statusBar()->showMessage(tr("Loading...", "This is a message in the status bar, that we are loading the file"), 0);
			pqapplication->processEvents();

			bool before=gt.rules.modified;
			gt.rules.modified=true;

			if(gt.rules.read(this, s)){
				students_schedule_ready=false;
				teachers_schedule_ready=false;
				rooms_schedule_ready=false;

				INPUT_FILENAME_XML = s;

				LockUnlock::computeLockedUnlockedActivitiesTimeSpace();
				LockUnlock::increaseCommunicationSpinBox();

				statusBar()->showMessage(tr("File opened"), STATUS_BAR_MILLISECONDS);

				gt.rules.modified=true;
				setRulesUnmodifiedAndOtherThings(&gt.rules);

				setCurrentFile(INPUT_FILENAME_XML);
			}
			else{
				gt.rules.modified=before;

				statusBar()->showMessage("", STATUS_BAR_MILLISECONDS);


				setCurrentFile(INPUT_FILENAME_XML);
			}


		}

		int tmp=s.lastIndexOf(FILE_SEP);
		WORKING_DIRECTORY=s.left(tmp);
	}
}
