address()
{
  if (d->invalid())
    return 0L;
  return d->addr.generic;
}
