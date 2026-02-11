insert (iterator pos, long n, const PhonebookEntry& x)
  throw(GsmException)
{
  for (long i = 0; i < n; i++)
    if (x.useIndex() && x.index() != -1)
      insert(x.telephone(), x.text(), x.index());
    else
      insertFirstEmpty(x.telephone(), x.text());
}
