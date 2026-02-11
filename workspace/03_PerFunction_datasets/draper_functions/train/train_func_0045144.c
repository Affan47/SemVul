misc_viper_bomb_prethink (edict_t * self)
{
  vec3_t v;
  float diff;

  self->groundentity = NULL;

  diff = self->timestamp - level.time;
  if (diff < -1.0)
    diff = -1.0;

  VectorScale (self->moveinfo.dir, 1.0 + diff, v);
  v[2] = diff;

  diff = self->s.angles[2];
  vectoangles (v, self->s.angles);
  self->s.angles[2] = diff + 10;
}
