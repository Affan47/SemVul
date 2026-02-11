popupDestroyed(QObject *obj)
{
	if ( prevPopups.contains((FancyPopup *)obj) ) {
		prevPopups.remove((FancyPopup *)obj);
		popup->move( position() );
	}
}
