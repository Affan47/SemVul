dispatch_event_to_broker(XEvent *e, unsigned long mask, struct module *m)
{
  Client *c;
  Icon *i;
  e->xany.display=(Display *)0;
  if(!XFindContext(dpy, e->xany.window, client_context, (XPointer *)&c))
    if(e->xany.window==c->window)
      e->xany.display=(Display *)1;
    else
      e->xany.display=(Display *)2;
  else if(!XFindContext(dpy, e->xany.window, icon_context, (XPointer *)&i))
    if(e->xany.window==i->window)
      e->xany.display=(Display *)3;

  while(m) {
    if(m->out_fd>=0 && ((m->broker.mask & mask)||(m->broker.exists && !mask))) {
      struct mcmd_event me;
      me.mask=mask;
      me.event=*e;
      reply_module(m, (char *)&me, ~sizeof(me));
      return 1;
    }
    m=m->next;
  }
  return 0;
}
