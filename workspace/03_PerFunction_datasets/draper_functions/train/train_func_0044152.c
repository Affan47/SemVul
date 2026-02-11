Resolver_EventProc (Tcl_Event *evPtr, int flags)
{
  ResolverEvent *ev = (ResolverEvent*) evPtr;
  ResolverData *data = (ResolverData*) ev->data;

  notify_callback(data->ip, data->callback_interp, data->callback);

  free(data->ip);
  free(data->host);
  Tcl_DecrRefCount (data->callback);

  ckfree(data);

  return 1;
}
