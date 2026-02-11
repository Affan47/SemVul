AuSetIOErrorHandler(AuServer *aud, AuIOErrorHandler handler)
{
    AuIOErrorHandler oldhandler = aud->funcs.ioerror_handler;

    if (!oldhandler)
       oldhandler = (AuIOErrorHandler) _AuDefaultIOError;

    aud->funcs.ioerror_handler = ((handler) ?
      (AuIOErrorHandler) handler :
       (AuIOErrorHandler) _AuDefaultIOError);

    return oldhandler;
}
