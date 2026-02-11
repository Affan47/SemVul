sendBackward()
{
	QLanguageItem* languageItem = dynamic_cast<QLanguageItem*>(sender());
	if ( !languageItem )
		languageItem = mFirstSelectedItem;
	if ( !languageItem )
		return;

	int index = mZOrderedItems.indexOf( languageItem );
	mZOrderedItems.move( index , MAX(0,index - 1) );
	updateZOrders();
}
