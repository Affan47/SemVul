Weapon_RocketLauncher_Fire (edict_t * ent)
{
  vec3_t offset, start;
  vec3_t forward, right;
  int damage;
  float damage_radius;
  int radius_damage;

  damage = 100 + (int) (random () * 20.0);
  radius_damage = 120;
  damage_radius = 120;
  if (is_quad)
    {
      damage *= 4;
      radius_damage *= 4;
    }

  AngleVectors (ent->client->v_angle, forward, right, NULL);

  VectorScale (forward, -2, ent->client->kick_origin);
  ent->client->kick_angles[0] = -1;

  VectorSet (offset, 8, 8, ent->viewheight - 8);
  P_ProjectSource (ent->client, ent->s.origin, offset, forward, right, start);
  fire_rocket (ent, start, forward, damage, 650, damage_radius,
	       radius_damage);


  gi.WriteByte (svc_muzzleflash);
  gi.WriteShort (ent - g_edicts);
  gi.WriteByte (MZ_ROCKET | is_silenced);
  gi.multicast (ent->s.origin, MULTICAST_PVS);

  ent->client->ps.gunframe++;

  PlayerNoise (ent, start, PNOISE_WEAPON);

  if (!((int) dmflags->value & DF_INFINITE_AMMO))
    ent->client->pers.inventory[ent->client->ammo_index]--;
}
