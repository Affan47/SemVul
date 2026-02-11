SP_path_corner (edict_t * self)
{
  if (!self->targetname)
    {
      gi.dprintf ("path_corner with no targetname at %s\n",
		  vtos (self->s.origin));
      G_FreeEdict (self);
      return;
    }

  self->solid = SOLID_TRIGGER;
  self->touch = path_corner_touch;
  VectorSet (self->mins, -8, -8, -8);
  VectorSet (self->maxs, 8, 8, 8);
  self->svflags |= SVF_NOCLIENT;
  gi.linkentity (self);
}
