yearChanged(const QString &yearName)
{
	int yearIndex=gt.rules.searchYear(yearName);
	if(yearIndex<0){
		groupsListWidget->clear();
		groupTextEdit->setPlainText(QString(""));
		return;
	}

	groupsListWidget->clear();

	StudentsYear* sty=gt.rules.yearsList.at(yearIndex);
	for(int i=0; i<sty->groupsList.size(); i++){
		StudentsGroup* stg=sty->groupsList[i];
		groupsListWidget->addItem(stg->name);
	}

	if(groupsListWidget->count()>0)
		groupsListWidget->setCurrentRow(0);
	else
		groupTextEdit->setPlainText(QString(""));
}
