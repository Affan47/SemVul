addHandler()
    {
    if( size == pos )
        {
        size += 16;
        handlers = static_cast< KXErrorHandler** >( qRealloc( handlers, size * sizeof( KXErrorHandler* )));
        }
    handlers[ pos++ ] = this;
    }
