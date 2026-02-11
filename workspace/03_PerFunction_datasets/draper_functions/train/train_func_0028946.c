do_redo ()
{
  int d;
  struct data *hp_b;
  struct dc *hp_c;
  struct spline *hp_sp;

  if (undo_get_redo_count () > 0)
    undo_redo ();

  if (hp->n > 0)
    {
      hp_b = da_root.next;
      if (hp_b->prev != &da_root)
	{
	  for (d = 0; d < hp->n; d++)
	    {
	      hp_b = hp_b->prev;
	      if (hp_b->prev == &da_root)
		{
		  da_root.next = hp_b;
		  break;
		}
	      da_root.next = hp_b;
	    }
	}
      for (d = 0; d < hp->n; d++)
	hp_b = hp_b->next;
      new = hp_b;
    }
  else
    {
      new = da_root.next;
      new->prev = &da_root;
    }

  if (hp->nc > 0)
    {
      hp_c = dac_root.next;
      if (hp_c->prev != &dac_root)
	{
	  for (d = 0; d < hp->nc; d++)
	    {
	      hp_c = hp_c->prev;
	      if (hp_c->prev == &dac_root)
		{
		  dac_root.next = hp_c;
		  break;
		}
	      dac_root.next = hp_c;
	    }
	}
      for (d = 0; d < hp->nc; d++)
	hp_c = hp_c->next;
      new_c = hp_c;
    }
  else
    {
      new_c = dac_root.next;
      new_c->prev = &dac_root;
    }

  if (hp->nsp > 0)
    {
      hp_sp = sp_root.next;
      if (hp_sp->prev != &sp_root)
	{
	  for (d = 0; d < hp->nsp; d++)
	    {
	      hp_sp = hp_sp->prev;
	      if (hp_sp->prev == &sp_root)
		{
		  sp_root.next = hp_sp;
		  break;
		}
	      sp_root.next = hp_sp;
	    }
	}
      for (d = 0; d < hp->nsp; d++)
	hp_sp = hp_sp->next;
      sp_new = hp_sp;
    }
  else
    {
      sp_new = sp_root.next;
      sp_new->prev = &sp_root;
    }

  FreePix ();
  CreatePix ();
  Display_Mol ();
}
