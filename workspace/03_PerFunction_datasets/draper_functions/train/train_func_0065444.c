xioErrhandler( Display* dpy )
{
    if(kapp)
    {
#ifdef Q_WS_X11
        d->oldXIOErrorHandler( dpy );
#else
        Q_UNUSED(dpy);
#endif
    }
    exit( 1 );
    return 0;
}
