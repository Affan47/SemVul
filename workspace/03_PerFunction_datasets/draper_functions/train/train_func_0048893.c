Hash_Free_Table(char *tbl)
{
  int tbl_size = Tbl_Size(tbl);
  HashNode *t = Hsh_Table(tbl);
  HashNode *endt = t + tbl_size;
  HashNode p, p1;

  do
    {
      p = *t;
      while (p)
	{
	  p1 = p;
	  p = p->next;
	  Free(p1);
	}
    }
  while (++t < endt);

  Free(tbl);
}
