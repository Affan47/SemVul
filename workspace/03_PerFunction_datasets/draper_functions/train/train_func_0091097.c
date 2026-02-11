on_selectOutputDirAction_activated()
{
	QString od;

	od = QFileDialog::getExistingDirectory(this, tr("Choose results (output) directory"), OUTPUT_DIR);

	if(!od.isNull()){
		QFile test(od+FILE_SEP+"test_write_permissions_3.tmp");
		bool existedBefore=test.exists();
		bool t=test.open(QIODevice::ReadWrite);


		if(!t){
			QMessageBox::warning(this, tr("FET warning"), tr("You don't have write permissions in this directory"));
			return;
		}
		test.close();
		if(!existedBefore)
			test.remove();

		OUTPUT_DIR=od;
	}
}
