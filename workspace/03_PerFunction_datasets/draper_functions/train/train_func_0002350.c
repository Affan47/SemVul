ThrowGib (edict_t * self, char *gibname, int damage, int type)
{
  edict_t *gib;
  vec3_t vd;
  vec3_t origin;
  vec3_t size;
  float vscale;

  gib = G_Spawn ();

  VectorScale (self->size, 0.5, size);
  VectorAdd (self->absmin, size, origin);
  gib->s.origin[0] = origin[0] + crandom () * size[0];
  gib->s.origin[1] = origin[1] + crandom () * size[1];
  gib->s.origin[2] = origin[2] + crandom () * size[2];

  gi.setmodel (gib, gibname);
  gib->solid = SOLID_NOT;
  gib->s.effects |= EF_GIB;
  gib->flags |= FL_NO_KNOCKBACK;
  gib->takedamage = DAMAGE_YES;
  gib->die = gib_die;

  if (type == GIB_ORGANIC)
    {
      gib->movetype = MOVETYPE_TOSS;
      gib->touch = gib_touch;
      vscale = 0.5;
    }
  else
    {
      gib->movetype = MOVETYPE_BOUNCE;
      vscale = 1.0;
    }

  VelocityForDamage (damage, vd);
  VectorMA (self->velocity, vscale, vd, gib->velocity);
  ClipGibVelocity (gib);
  gib->avelocity[0] = random () * 600;
  gib->avelocity[1] = random () * 600;
  gib->avelocity[2] = random () * 600;

  gib->think = G_FreeEdict;
  gib->nextthink = level.time + 10 + random () * 10;

  gi.linkentity (gib);
}
