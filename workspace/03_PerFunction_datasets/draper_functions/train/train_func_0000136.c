traceSubObjects(Collector &c) const
{
  c.trace(flowObj_);
  if (display_)
    for (ELObj **p = display_; *p; p++)
      c.trace(*p);
}
