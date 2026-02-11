track() const
{
  if(!d->frameListMap["TRCK"].isEmpty())
    return d->frameListMap["TRCK"].front()->toString().toInt();
  return 0;
}
