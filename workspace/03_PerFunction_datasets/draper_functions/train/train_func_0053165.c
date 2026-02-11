PANRATE(Ui::ConfigurationClass * configUi, const ConfigLine * configLine, Direction dir)
{
	outDebug(4,std::cout << "PANRATE" << std::endl);
	if (dir == toScreen)
	{
		std::string panRateSpin = configLine->getLowercaseToken(1);
		if (panRateSpin.length() == 0)
			configLine->setInError(configLine->getAbsoluteTokenColumn(1));
		if (panRateSpin[0] == '+') panRateSpin = panRateSpin.substr(1);
		int num = parseNum(panRateSpin);
		if (panRateSpin.length() > 0 && num == 0)
		{
			if (panRateSpin.compare("fast") == 0) num=50;
			else if (panRateSpin.compare("slow") == 0) num=500;
			else
			{
				num = 500;
				configLine->setInError(configLine->getAbsoluteTokenColumn(1));
			}
		}
		configUi->panRateSpin->setValue(num);
		mSpinMap["PANRATE"] = configUi->panRateSpin->value();
		if (configLine->getToken(2).length() != 0)
			configLine->setInError(configLine->getAbsoluteTokenColumn(2));
	}
	else
	{

		if (mSpinMap["PANRATE"] != configUi->panRateSpin->value())
			const_cast<ConfigLine *>(configLine)->replaceParameters(configUi->panRateSpin->text().toStdString());
	}
}
