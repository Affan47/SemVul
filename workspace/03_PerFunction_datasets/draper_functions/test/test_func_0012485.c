setPath( const QPainterPath& p )
{
	QGraphicsPathItem::setPath(p);

	setText( mText->text() );
}
