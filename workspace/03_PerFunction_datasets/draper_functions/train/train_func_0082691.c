zbufalc (c)
     size_t c;
{
  register struct sbuf *q;

  if (qBlist == NULL)
    {
      q = (struct sbuf *) xmalloc (sizeof (struct sbuf) + c - 4);
      q->c = c;
    }
  else
    {
      q = qBlist;
      qBlist = q->qnext;
      if (q->c < c)
	{
	  q = (struct sbuf *) xrealloc ((pointer) q,
					sizeof (struct sbuf) + c - 4);
	  q->c = c;
	}
    }
  return q->u.ab;
}
