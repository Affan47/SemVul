setDoPost( bool enable )
{
    if ( !d )
        d = new BrowserArgumentsPrivate;
    d->doPost = enable;
}
