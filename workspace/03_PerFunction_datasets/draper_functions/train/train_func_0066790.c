_AuDoDeqAsyncHandler(AuServer *aud, _AuAsyncHandler *handler)
{
    _AuAsyncHandler **prev;
    _AuAsyncHandler *async;

    for (prev = &aud->async_handlers;
	 (async = *prev) && (async != handler);
	 prev = &async->next)

	;
    if (async)
	*prev = async->next;
}
