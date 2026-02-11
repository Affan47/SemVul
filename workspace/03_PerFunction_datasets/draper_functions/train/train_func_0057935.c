trace(Collector &c) const
{
  if (sp) {
    for (ELObj **p = sbase; p != sp; p++)
      c.trace(*p);
  }
  for (ControlStackEntry *p = csbase; p != csp; p++) {
    c.trace(p->protectClosure);
    c.trace(p->continuation);
  }
  c.trace(protectClosure);
}
