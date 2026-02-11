notify(QObject *receiver, QEvent *event)
{
#ifdef Q_WS_X11
	if( event->type() == QEvent::Show && receiver->isWidgetType())
	{
		QWidget* w = static_cast< QWidget* >( receiver );
		if( w->isTopLevel() && qt_x_last_input_time != CurrentTime )
			XChangeProperty( QX11Info::display(), w->winId(), kde_net_wm_user_time, XA_CARDINAL,
					 32, PropModeReplace, (unsigned char*)&qt_x_last_input_time, 1 );
	}
	if( event->type() == QEvent::Hide && receiver->isWidgetType())
	{
		QWidget* w = static_cast< QWidget* >( receiver );
		if( w->isTopLevel() && w->winId() != 0 )
			XDeleteProperty( QX11Info::display(), w->winId(), kde_net_wm_user_time );
	}
#endif
	return QApplication::notify(receiver, event);
}
