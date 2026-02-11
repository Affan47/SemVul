centerOnScreen( QWidget *widget, int screen )
{
  if ( !widget )
    return;

#ifdef Q_WS_X11
  if( !( widget->windowFlags() & Qt::X11BypassWindowManagerHint ) && widget->windowType() != Qt::Popup
      && NETRootInfo( QX11Info::display(), NET::Supported ).isSupported( NET::WM2FullPlacement )) {
      return;
  }
#endif

  QRect rect = screenRect( widget, screen );

  widget->move( rect.center().x() - widget->width() / 2,
                rect.center().y() - widget->height() / 2 );
}
