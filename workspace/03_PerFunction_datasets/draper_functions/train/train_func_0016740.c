searchCatalogs(const QString& text, QList<CatItem> & out)
{
	gSearchText = text.toLower();
	QList<CatItem*> catMatches = search(gSearchText);


	qSort(catMatches.begin(), catMatches.end(), CatLess);


	QString location = "History/" + gSearchText;
	QStringList hist;
	hist = gSettings->value(location, hist).toStringList();
	if (hist.count() == 2)
	{
		for (int i = 0; i < catMatches.count(); i++)
		{
			if (catMatches[i]->lowName == hist[0] &&
				catMatches[i]->fullPath == hist[1])
			{
				CatItem* tmp = catMatches[i];
				catMatches.removeAt(i);
				catMatches.push_front(tmp);
			}
		}
	}


	int max = gSettings->value("GenOps/numresults", 10).toInt();
	for (int i = 0; i < max && i < catMatches.count(); i++)
	{
		out.push_back(*catMatches[i]);
	}
}
