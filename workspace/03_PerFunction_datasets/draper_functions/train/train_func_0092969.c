addNumericDisplay( NumericDisplayItem * displayItem )
{
	addItem( displayItem );
	displayItem->setPos( -1000000, 0 );
	m_numericDisplays << displayItem;
}
