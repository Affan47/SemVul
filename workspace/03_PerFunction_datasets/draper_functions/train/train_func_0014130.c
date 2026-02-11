door_use_areaportals (edict_t * self, qboolean open)
{
  edict_t *t = NULL;

  if (!self->target)
    return;

  while ((t = G_Find (t, FOFS (targetname), self->target)))
    {
      if (Q_stricmp (t->classname, "func_areaportal") == 0)
	{
	  gi.SetAreaPortalState (t->style, open);
	}
    }
}
