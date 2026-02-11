add_timeout(Timeout::Internal *wi)
{
  Timeout *t = new Glib::BusTimeout(wi, _ctx, _priority);

  debug_log("glib: added timeout %p (%s)", t, t->enabled() ? "on" : "off");

  return t;
}
