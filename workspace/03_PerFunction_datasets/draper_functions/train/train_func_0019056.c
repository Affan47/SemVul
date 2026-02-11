schedule_rotate_up (struct schedule *s, struct schedule_entry *e)
{
  if (e && e->parent)
    {
      struct schedule_entry *lt = e->lt;
      struct schedule_entry *gt = e->gt;
      struct schedule_entry *p = e->parent;
      struct schedule_entry *gp = p->parent;

      if (gp)
	{
	  if (gp->gt == p)
	    gp->gt = e;
	  else if (gp->lt == p)
	    gp->lt = e;
	  else
	    {
	      ASSERT (0);
	    }
	}
      else
	{
	  s->root = e;
	}


      e->parent = gp;


      p->parent = e;


      if (p->gt == e)
	{
	  e->lt = p;
	  p->gt = lt;
	  if (lt)
	    lt->parent = p;
	}
      else if (p->lt == e)
	{
	  e->gt = p;
	  p->lt = gt;
	  if (gt)
	    gt->parent = p;
	}
      else
	{

	  ASSERT (0);
	}

#ifdef SCHEDULE_TEST
      ++z.sru;
#endif
    }
}
