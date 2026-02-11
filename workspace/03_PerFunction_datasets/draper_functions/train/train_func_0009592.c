setHeader(Header *h, bool deleteCurrent)
{
  if(deleteCurrent)
    delete d->header;

  d->header = h;
}
