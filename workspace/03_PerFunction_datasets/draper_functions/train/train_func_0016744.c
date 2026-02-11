contextMenuEvent ( QGraphicsSceneContextMenuEvent * event )
{
	if (mIsStorageModeOn)
		return;

	if ( scene()->selectedItems().size() > 1 )
	{
		event->ignore();
		return;
	}

	QMenu * m = buildContextMenu();
	if ( m )
	{
		event->accept();
		m->exec( event->screenPos() );
		delete m;
	}
}
