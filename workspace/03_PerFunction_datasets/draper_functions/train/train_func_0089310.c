toString() const
{
  return d->email + " rating=" + String::number(d->rating) + " counter=" + String::number(d->counter);
}
