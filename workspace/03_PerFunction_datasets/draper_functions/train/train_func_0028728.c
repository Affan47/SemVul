saveAll()
{
	QList<QLanguageItem*> items = languageItems();
	for ( int i = 0 ; i < items.size() ; i++ )
	{
		if ( !items[i]->file().isEmpty() )
		{
			items[i]->saveItem();
		}
	}

	saveScene();
}
