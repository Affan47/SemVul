interference_event (Display *dpy, Window window, void *closure, XEvent *event)
{
#if HAVE_XSHM_EXTENSION
  struct inter_context *c = (struct inter_context *) closure;

  if(c->use_shm && event->type == XShmGetEventBase(dpy) + ShmCompletion)
  {
    c->shm_can_draw = True;
    return True;
  }
#endif
  return False;
}
