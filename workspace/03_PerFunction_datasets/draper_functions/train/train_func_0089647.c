handleText(QLineEdit * lineEdit, const ConfigLine * configLine, Direction dir)
{
	std::string parm = configLine->getToken(1);
	outDebug(4,std::cout << configLine->getToken(0) << std::endl);
	if (dir == toScreen)
	{
		if (configLine->getToken(2).length() != 0)
			configLine->setInError(configLine->getAbsoluteTokenColumn(2));
		lineEdit->setText(parm.c_str());
	}
	else
	{

		if (lineEdit->isModified())
		{
			const_cast<ConfigLine *>(configLine)->replaceParameters(lineEdit->text().toStdString());
		}
	}
}
