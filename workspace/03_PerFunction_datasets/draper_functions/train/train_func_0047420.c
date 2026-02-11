schedule_insert (struct schedule *s, struct schedule_entry *e)
{
  struct schedule_entry *c = s->root;
  while (true)
    {
      const int comp = schedule_entry_compare (e, c);

#ifdef SCHEDULE_TEST
      ++z.ins;
#endif

      if (comp == -1)
	{
	  if (c->lt)
	    {
	      c = c->lt;
	      continue;
	    }
	  else
	    {
	      c->lt = e;
	      e->parent = c;
	      break;
	    }
	}
      else if (comp == 1)
	{
	  if (c->gt)
	    {
	      c = c->gt;
	      continue;
	    }
	  else
	    {
	      c->gt = e;
	      e->parent = c;
	      break;
	    }
	}
      else
	{


#ifdef SCHEDULE_TEST
	  ++z.coll;
#endif
	  schedule_set_pri (e);

	  c = s->root;
	  continue;
	}
    }
}
