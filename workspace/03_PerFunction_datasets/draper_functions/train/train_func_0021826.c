genie_skip (NODE_T * p)
{
  PROP_T self;
  if (MOID (p) != MODE (VOID)) {
    genie_push_undefined (p, MOID (p));
  }
  UNIT (&self) = genie_skip;
  SOURCE (&self) = p;
  return (self);
}
