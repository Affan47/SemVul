getResults(QList<InputData>* inputData, QList<CatItem>* results)
{
	if (inputData->count() == 2)
	{
		QString text = inputData->at(1).getText();

		if (inputData->first().hasLabel(HASH_DIR))
		{
			addCatItem(text, results, "Properties", "Directory properties", "properties.png");
		}
		else if (inputData->first().hasLabel(HASH_FILE))
		{
			addCatItem(text, results, "Open containing folder", "Open containing folder", "opencontainer.png");
			addCatItem(text, results, "Properties", "File properties", "properties.png");
		}
		else if (inputData->first().hasLabel(HASH_LINK))
		{
			addCatItem(text, results, "Run as", "Run as a different user", "run.png");
			addCatItem(text, results, "Open containing folder", "Open containing folder", "opencontainer.png");
			addCatItem(text, results, "Open shortcut folder", "Open shortcut folder", "opencontainer.png");
			addCatItem(text, results, "Copy path", "Copy path to clipboard", "copy.png");
			addCatItem(text, results, "Properties", "File properties", "properties.png");
		}
		else
		{
			return;
		}


		inputData->first().setID(HASH_VERBY);
		inputData->first().getTopResult().id = HASH_VERBY;


		results->push_front(CatItem(
			"Run",
			inputData->last().getText(), INT_MAX,
			getIconPath() + "run.png"));
	}
}
