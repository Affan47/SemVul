P_GunShot
( mobj_t*	mo,
  boolean	accurate )
{
    angle_t	angle;
    int		damage;

    damage = 5*(P_Random ()%3+1);
    angle = mo->angle;

    if (!accurate)
	angle += (P_Random()-P_Random())<<18;

    P_LineAttack (mo, angle, MISSILERANGE, bulletslope, damage);
}
