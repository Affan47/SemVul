currentDesktop()
{
    if (!QX11Info::display())
      return 1;

    if( mapViewport()) {
        init( INFO_BASIC );
        KWindowSystemPrivate* const s_d = s_d_func();
        NETPoint p = s_d->desktopViewport( s_d->currentDesktop( true ));
        return viewportToDesktop( QPoint( p.x, p.y ));
    }

    KWindowSystemPrivate* const s_d = s_d_func();
    if( s_d )
        return s_d->currentDesktop( true );
    NETRootInfo info( QX11Info::display(), NET::CurrentDesktop );
    return info.currentDesktop( true );
}
