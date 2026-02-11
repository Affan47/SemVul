followMatch(int pos, int len)
{
  int previous = pos + len;
  for (;;)
    {
      QMap<int,Mch>::iterator it = d->matches.find(previous);
      if (it == d->matches.end())
        return pos;
      pos = it->pos;
      len = it->len;
      previous = it->previous;
    }
}
