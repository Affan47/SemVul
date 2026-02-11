_AuError (AuServer *aud, auError *rep)
{


    AuEvent event;
    _AuAsyncHandler *async, *next;

    event.auerror.serial = _AuSetLastRequestRead(aud, (auGenericReply *)rep);

    for (async = aud->async_handlers; async; async = next) {
	next = async->next;
	if ((*async->handler)(aud, (auReply *)rep,
			      (char *)rep, SIZEOF(auError), async->data))
	    return 0;
    }

    event.auerror.server = aud;
    event.auerror.type = Au_Error;
    event.auerror.time = rep->time;
    event.auerror.resourceid = rep->resourceID;
    event.auerror.error_code = rep->errorCode;
    event.auerror.request_code = rep->majorCode;
    event.auerror.minor_code = rep->minorCode;
    switch (event.auerror.error_code) {
      default:
	event.auerror.data.l[0] = rep->data0;
	event.auerror.data.l[1] = rep->data1;
	event.auerror.data.l[2] = rep->data2;
	event.auerror.data.l[3] = rep->data3;
    }

    if (aud->error_vec &&
	!(*aud->error_vec[rep->errorCode])(aud, &event.auerror, rep))
	return 0;
    if (aud->funcs.error_handler != NULL) {
      	return ((*aud->funcs.error_handler)(aud, (AuErrorEvent *) &event));
    } else {
	return _AuDefaultError(aud, (AuErrorEvent *) &event);
    }
}
