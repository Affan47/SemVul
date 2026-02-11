P_BulletSlope (mobj_t*	mo)
{
    angle_t	an;


    an = mo->angle;
    bulletslope = P_AimLineAttack (mo, an, 16*64*FRACUNIT);

    if (!linetarget)
    {
	an += 1<<26;
	bulletslope = P_AimLineAttack (mo, an, 16*64*FRACUNIT);
	if (!linetarget)
	{
	    an -= 2<<26;
	    bulletslope = P_AimLineAttack (mo, an, 16*64*FRACUNIT);
	}
    }
}
