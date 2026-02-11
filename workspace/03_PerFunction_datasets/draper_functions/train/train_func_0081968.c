resizeEvent( QResizeEvent * )
{
	scene()->setSceneRect( QRectF(0,0,width() - HISTORY_ITEM_MARGIN , MAX( height() - SCROLL_BAR_MARGIN , scene()->sceneRect().height() ) ) );
}
