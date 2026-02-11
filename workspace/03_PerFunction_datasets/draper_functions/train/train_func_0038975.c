error( bool sync ) const
    {
    if( sync )
        XSync( d->display, False );
    return d->was_error;
    }
