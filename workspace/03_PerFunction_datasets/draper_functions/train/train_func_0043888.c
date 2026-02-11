fireMissile (int id, AIObj **missile, AIObj *target)
{
  int i;
  if (!haveMissile (id)) return false;
  if (ttf > 0) return false;
  for (i = 0; i < maxmissile; i ++)
  {
    if (missile [i]->ttl <= 0) break;
  }
  if (i < maxmissile)
  {
    fireMissile2 (id, missile [i], target);
    decreaseMissile (id);
    firemissilettl = 20 * timestep;
    return true;
  }
  return false;
}
