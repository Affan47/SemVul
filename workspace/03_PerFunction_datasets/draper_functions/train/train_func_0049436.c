addItem( QLanguageItem * container )
{
	setupContainer(container);

	container->setPos(0,0);


	QRectF rect = container->sceneBoundingRect();
	float scaleFactor = MIN( float(STORAGE_ITEM_WIDTH) / rect.width() , float(STORAGE_ITEM_HEIGHT) / rect.height() );
	scaleFactor = MIN( MIN(scaleFactor,1.0f/container->transform().m11()) , MIN(scaleFactor,1.0f/container->transform().m22()) );
	container->scale( scaleFactor , scaleFactor );


	container->setFlags( QGraphicsItem::ItemIsSelectable );


	scene()->addItem( container );
	mAddedItems.append( container );

	reorderItems();
}
