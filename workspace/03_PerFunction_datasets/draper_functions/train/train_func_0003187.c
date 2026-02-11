year() const
{
  if(d->items.contains("\251day"))
    return d->items["\251day"].toStringList().toString().toInt();
  return 0;
}
