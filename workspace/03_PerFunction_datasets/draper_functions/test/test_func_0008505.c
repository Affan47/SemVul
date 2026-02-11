P_ZMovement (mobj_t* mo)
{
    fixed_t	dist;
    fixed_t	delta;


    if (mo->player && mo->z < mo->floorz)
    {
	mo->player->viewheight -= mo->floorz-mo->z;

	mo->player->deltaviewheight
	    = (VIEWHEIGHT - mo->player->viewheight)>>3;
    }


    mo->z += mo->momz;

    if ( mo->flags & MF_FLOAT
	 && mo->target)
    {

	if ( !(mo->flags & MF_SKULLFLY)
	     && !(mo->flags & MF_INFLOAT) )
	{
	    dist = P_AproxDistance (mo->x - mo->target->x,
				    mo->y - mo->target->y);

	    delta =(mo->target->z + (mo->height>>1)) - mo->z;

	    if (delta<0 && dist < -(delta*3) )
		mo->z -= FLOATSPEED;
	    else if (delta>0 && dist < (delta*3) )
		mo->z += FLOATSPEED;
	}

    }


    if (mo->z <= mo->floorz)
    {


	int correct_lost_soul_bounce = gameversion >= exe_ultimate;

	if (correct_lost_soul_bounce && mo->flags & MF_SKULLFLY)
	{

	    mo->momz = -mo->momz;
	}

	if (mo->momz < 0)
	{
	    if (mo->player
		&& mo->momz < -GRAVITY*8)
	    {


		mo->player->deltaviewheight = mo->momz>>3;
		S_StartSound (mo, sfx_oof);
	    }
	    mo->momz = 0;
	}
	mo->z = mo->floorz;


        if (!correct_lost_soul_bounce && mo->flags & MF_SKULLFLY)
            mo->momz = -mo->momz;

	if ( (mo->flags & MF_MISSILE)
	     && !(mo->flags & MF_NOCLIP) )
	{
	    P_ExplodeMissile (mo);
	    return;
	}
    }
    else if (! (mo->flags & MF_NOGRAVITY) )
    {
	if (mo->momz == 0)
	    mo->momz = -GRAVITY*2;
	else
	    mo->momz -= GRAVITY;
    }

    if (mo->z + mo->height > mo->ceilingz)
    {

	if (mo->momz > 0)
	    mo->momz = 0;
	{
	    mo->z = mo->ceilingz - mo->height;
	}

	if (mo->flags & MF_SKULLFLY)
	{
	    mo->momz = -mo->momz;
	}

	if ( (mo->flags & MF_MISSILE)
	     && !(mo->flags & MF_NOCLIP) )
	{
	    P_ExplodeMissile (mo);
	    return;
	}
    }
}
