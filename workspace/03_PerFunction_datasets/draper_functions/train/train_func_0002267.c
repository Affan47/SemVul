make_complex_modes (enum mode_class cl,
		    const char *file, unsigned int line)
{
  struct mode_data *m;
  struct mode_data *c;
  char buf[8];
  enum mode_class cclass = complex_class (cl);

  if (cclass == MODE_RANDOM)
    return;

  for (m = modes[cl]; m; m = m->next)
    {

      if (m->precision == 1)
	continue;

      if (strlen (m->name) >= sizeof buf)
	{
	  error ("%s:%d:mode name \"%s\" is too long",
		 m->file, m->line, m->name);
	  continue;
	}


      if (cl == MODE_FLOAT)
	{
	  char *p, *q = 0;
	  strncpy (buf, m->name, sizeof buf);
	  p = strchr (buf, 'F');
	  if (p == 0)
	    q = strchr (buf, 'D');
	  if (p == 0 && q == 0)
	    {
	      error ("%s:%d: float mode \"%s\" has no 'F' or 'D'",
		     m->file, m->line, m->name);
	      continue;
	    }

	  if (p != 0)
	    *p = 'C';
	  else
	    snprintf (buf, sizeof buf, "C%s", m->name);
	}
      else
	snprintf (buf, sizeof buf, "C%s", m->name);

      c = new_mode (cclass, xstrdup (buf), file, line);
      c->component = m;
    }
}
