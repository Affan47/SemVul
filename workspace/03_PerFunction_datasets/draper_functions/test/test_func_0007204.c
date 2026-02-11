position()
{
	QRect geom = qApp->desktop()->availableGeometry(popup);
	QPoint destination(geom.x() + geom.width(), geom.y() + geom.height());

	if ( destination.y() > (qApp->desktop()->screenGeometry().height()/2) )
		popupLayout = Private::BottomToTop;
	else
		popupLayout = Private::TopToBottom;

	if ( (destination.x() + popup->width()) > (geom.x() + geom.width()) )
		destination.setX( geom.x() + geom.width() - popup->width() );

	if ( destination.x() < 0 )
		destination.setX( 0 );

	if ( (destination.y() + popup->height()) > (geom.y() + geom.height()) )
		destination.setY( geom.y() + geom.height() - popup->height() );

	if ( destination.y() < 0 )
		destination.setY( 0 );

	foreach ( FancyPopup *p, prevPopups )
		destination.setY( destination.y() + popupLayout * p->height() );

	return destination;
}
