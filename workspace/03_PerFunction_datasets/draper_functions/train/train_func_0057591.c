ReadByte(void *pp)
{
  CByteInToLook *p = (CByteInToLook *)pp;
  if (p->cur != p->end)
    return *p->cur++;
  if (p->res == SZ_OK)
  {
    size_t size = p->cur - p->begin;
    p->processed += size;
    p->res = p->inStream->Skip(p->inStream, size);
    size = (1 << 25);
    p->res = p->inStream->Look(p->inStream, (const void **)&p->begin, &size);
    p->cur = p->begin;
    p->end = p->begin + size;
    if (size != 0)
      return *p->cur++;;
  }
  p->extra = True;
  return 0;
}
