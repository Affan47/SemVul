gend()
{
  d->count -= 1;
  if (d->count <= 0 && d->p)
    {
      refresh();
      d->count = 0;
    }
}
