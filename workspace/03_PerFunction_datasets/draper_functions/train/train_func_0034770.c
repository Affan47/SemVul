write(){
	mutex.lock();

	Solution& c=gen.c;


	QString tmp;
	c.fitness(gt.rules, &tmp);

	TimetableExport::getStudentsTimetable(c);
	TimetableExport::getTeachersTimetable(c);
	TimetableExport::getRoomsTimetable(c);


	conflictsStringTitle=TimetableGenerateForm::tr("Conflicts", "Title of dialog");
	conflictsString="";
	conflictsString+=TimetableGenerateForm::tr("Total conflicts:");
	conflictsString+=" ";
	conflictsString+=CustomFETString::number(c.conflictsTotal);
	conflictsString+="\n";
	conflictsString+=TimetableGenerateForm::tr("Conflicts listing (in decreasing order):");
	conflictsString+="\n";

	foreach(QString t, c.conflictsDescriptionList)
		conflictsString+=t+"\n";

	TimetableExport::writeSimulationResults(this);

	mutex.unlock();

	QString kk;
	kk=FILE_SEP;
	if(INPUT_FILENAME_XML=="")
		kk.append("unnamed");
	else{
		kk.append(INPUT_FILENAME_XML.right(INPUT_FILENAME_XML.length()-INPUT_FILENAME_XML.lastIndexOf(FILE_SEP)-1));

		if(kk.right(4)==".fet")
			kk=kk.left(kk.length()-4);
	}
	kk.append("-single");

	QMessageBox::information(this, TimetableGenerateForm::tr("FET information"),
		TimetableGenerateForm::tr("Simulation results should now be written in the directory %1 in html and xml mode"
		" and the conflicts in txt mode").arg(QDir::toNativeSeparators(OUTPUT_DIR+FILE_SEP+"timetables"+kk)));
}
