start_iowatch(int fd, const Callback::CallbackArg<TypeTuple<GIOCondition, bool&> >* cb,
		    Releaser& r, GIOCondition io_condition, gint priority,
		    GMainContext* context_p) {


  Callback::SafeFunctorArg<TypeTuple<GIOCondition, bool&> > f(cb);

  GSource* source_p = g_source_new(&cgu_io_watch_source_condition_funcs, sizeof(WatchSourceCondition));


  WatchSourceCondition* watch_source_p = reinterpret_cast<WatchSourceCondition*>(source_p);
  watch_source_p->poll_fd.fd = fd;
  watch_source_p->poll_fd.events = io_condition;
  watch_source_p->poll_fd.revents = 0;
  watch_source_p->watch_condition = io_condition;
  watch_source_p->emitter_p = 0;
  try {
    watch_source_p->emitter_p = new SafeEmitterArg<TypeTuple<GIOCondition, bool&> >;
    watch_source_p->emitter_p->connect(f, r);
  }
  catch (...) {
    delete watch_source_p->emitter_p;
    g_source_unref(source_p);
    throw;
  }

  g_source_set_priority(source_p, priority);


  g_source_add_poll(source_p, &watch_source_p->poll_fd);


  guint id = g_source_attach(source_p, context_p);


  g_source_unref(source_p);

  return id;
}

}
