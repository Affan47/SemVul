Common_Clean(SRInf *sr, Bool for_reread)
{
  SROneDirect *o, *o1;
  SRModule *m, *m1;

  if (for_reread || (sr->mask & UNDO_DIRECTIVES_MASK) != 0)
    {
      if (sr->cur_module)
	Undo_Directives(&sr->cur_module->direct_lst);
      Undo_Directives(&sr->direct_lst);
    }

  o = sr->direct_lst.first;
  while(o)
    {
      o1 = o;
      o = o->next;
      Free(o1);
    }

  m = sr->module_lst;
  while(m)
    {
      o = m->direct_lst.first;
      while(o)
	{
	  o1 = o;
	  o = o->next;
	  Free(o1);
	}
      m1 = m;
      m = m->next;
      Free(m);
    }

  if (for_reread)
    {
      sr->cur_l1 = sr->cur_l2 = 0;
      sr->char_count = 0;
      sr->line_count = 0;
      sr->error_count = 0;
      sr->warning_count = 0;
      sr->direct_lst.first = NULL;
      sr->direct_lst.last = NULL;

      sr->module_lst = NULL;
      sr->cur_module = NULL;
      sr->interface = FALSE;
    }
}
