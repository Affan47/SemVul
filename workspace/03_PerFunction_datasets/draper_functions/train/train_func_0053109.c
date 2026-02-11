setPickRoot(SoNode * node)
{
  SoNode * oldroot = PRIVATE(this)->pickroot;
  PRIVATE(this)->pickroot = node;
  if (PRIVATE(this)->pickroot) PRIVATE(this)->pickroot->ref();
  if (oldroot) oldroot->unref();
  PRIVATE(this)->pickvalid = FALSE;
}
