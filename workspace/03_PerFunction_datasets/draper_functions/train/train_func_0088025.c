filterItems(const QList<QGraphicsItem*>& list)
{
	QList<QLanguageItem*> result;
	for ( int i = 0 ; i < list.size() ; i++ )
	{
		QLanguageItem * languageItem = dynamic_cast<QLanguageItem*> (list[i]);
		if ( languageItem )
			result.append( languageItem );
	}
	return result;
}
