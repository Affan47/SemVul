SP_misc_viper_bomb (edict_t * self)
{
  self->movetype = MOVETYPE_NONE;
  self->solid = SOLID_NOT;
  VectorSet (self->mins, -8, -8, -8);
  VectorSet (self->maxs, 8, 8, 8);

  self->s.modelindex = gi.modelindex ("models/objects/bomb/tris.md2");

  if (!self->dmg)
    self->dmg = 1000;

  self->use = misc_viper_bomb_use;
  self->svflags |= SVF_NOCLIENT;

  gi.linkentity (self);
}
