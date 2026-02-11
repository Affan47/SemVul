exportCSVActivityTags(QWidget* parent, QString& lastWarnings, const QString textquote, const bool head, const QString setSeparator, QMessageBox::StandardButton& msgBoxButton){
	QString s2=INPUT_FILENAME_XML.right(INPUT_FILENAME_XML.length()-INPUT_FILENAME_XML.lastIndexOf(FILE_SEP)-1);

	if(s2.right(4)==".fet")
		s2=s2.left(s2.length()-4);


	QString UNDERSCORE="_";
	if(INPUT_FILENAME_XML=="")
		UNDERSCORE="";
	QString file=PREFIX_CSV+s2+UNDERSCORE+CSVActivityTags;

	if(!Export::okToWrite(parent, file, msgBoxButton))
		return false;

	QFile fileExport(file);
	if(!fileExport.open(QIODevice::WriteOnly)){
		lastWarnings+=Export::tr("FET critical. Cannot open file %1 for writing. Please check your disk's free space. Saving of %1 aborted.").arg(file)+"\n";
		return false;
		assert(0);
	}
	QTextStream tosExport(&fileExport);
	tosExport.setCodec("UTF-8");
	tosExport.setGenerateByteOrderMark(true);

	if(head)
		tosExport<<textquote<<"Activity Tag"<<textquote<<endl;

	foreach(ActivityTag* a, gt.rules.activityTagsList){
		tosExport<<textquote<<protectCSV(a->name)<<textquote<<endl;
		if(!checkSetSeparator(a->name, setSeparator))
			lastWarnings+=Export::tr("Warning! Import of activities will fail, because %1 include set separator +.").arg(a->name)+"\n";
	}

	lastWarnings+=Export::tr("%1 activity tags exported.").arg(gt.rules.activityTagsList.size())+"\n";
	if(fileExport.error()>0){
		lastWarnings+=Export::tr("FET critical. Writing %1 gave error code %2, which means saving is compromised. Please check your disk's free space.").arg(file).arg(fileExport.error()+"\n");
		return false;
	}
	fileExport.close();
	return true;
}
