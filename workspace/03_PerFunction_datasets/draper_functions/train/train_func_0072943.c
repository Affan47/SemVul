note_yacc_type (options_p o, pair_p fields, pair_p typeinfo,
		struct fileloc *pos)
{
  pair_p p;
  pair_p *p_p;

  for (p = typeinfo; p; p = p->next)
    {
      pair_p m;

      if (p->name == NULL)
	continue;

      if (p->type == (type_p) 1)
	{
	  pair_p pp;
	  int ok = 0;

	  for (pp = typeinfo; pp; pp = pp->next)
	    if (pp->type != (type_p) 1
		&& strcmp (pp->opt->info, p->opt->info) == 0)
	      {
		ok = 1;
		break;
	      }
	  if (! ok)
	    continue;
	}

      for (m = fields; m; m = m->next)
	if (strcmp (m->name, p->name) == 0)
	  p->type = m->type;
      if (p->type == NULL)
	{
	  error_at_line (&p->line,
			 "couldn't match fieldname `%s'", p->name);
	  p->name = NULL;
	}
    }

  p_p = &typeinfo;
  while (*p_p)
    {
      pair_p p = *p_p;

      if (p->name == NULL
	  || p->type == (type_p) 1)
	*p_p = p->next;
      else
	p_p = &p->next;
    }

  new_structure ("yy_union", 1, pos, typeinfo, o);
  do_typedef ("YYSTYPE", find_structure ("yy_union", 1), pos);
}
