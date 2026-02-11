is_float (Client * c)
{
  int i;

  if (!c->class)
    return 0;

  for (i = 0; i < MAXFLOATCLASS; i++)
    {
      char *inst;

      if (!prefs.floatclass[i])
	continue;

      if (strcmp (c->class, prefs.floatclass[i]) == 0)
	return 1;

      if (!c->instance)
	return 0;

      if (strcmp (c->instance, prefs.floatclass[i]) == 0)
	return 1;

      if ((inst = strchr (prefs.floatclass[i], '~')))
	{
	  inst++;
	  if (strncmp (c->class, prefs.floatclass[i], strlen (c->class)) == 0)
	    if (strncmp (c->instance, inst, strlen (c->instance)) == 0)
	      return 1;
	}
    }

  return 0;
}
