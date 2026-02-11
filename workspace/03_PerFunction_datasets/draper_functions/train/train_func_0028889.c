transientFor( WId win )
{
    KXErrorHandler handler;
    Window transient_for = None;
    if( XGetTransientForHint( QX11Info::display(), win, &transient_for ))
        return transient_for;

    return None;
}
