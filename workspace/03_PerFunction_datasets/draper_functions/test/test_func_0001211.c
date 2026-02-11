load(const ActionInstance *actionInstance)
	{
		QString textBuffer = actionInstance->subParameter(name().original(), "value").value().toString();

		mItemListWidget->setItems(textBuffer.split('\n', QString::SkipEmptyParts));
	}
