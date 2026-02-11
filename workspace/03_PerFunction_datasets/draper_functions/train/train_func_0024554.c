T_MoveFloor(floormove_t* floor)
{
    result_e	res;

    res = T_MovePlane(floor->sector,
		      floor->speed,
		      floor->floordestheight,
		      floor->crush,0,floor->direction);

    if (!(leveltime&7))
	S_StartSound(&floor->sector->soundorg, sfx_stnmov);

    if (res == pastdest)
    {
	floor->sector->specialdata = NULL;

	if (floor->direction == 1)
	{
	    switch(floor->type)
	    {
	      case donutRaise:
		floor->sector->special = floor->newspecial;
		floor->sector->floorpic = floor->texture;
	      default:
		break;
	    }
	}
	else if (floor->direction == -1)
	{
	    switch(floor->type)
	    {
	      case lowerAndChange:
		floor->sector->special = floor->newspecial;
		floor->sector->floorpic = floor->texture;
	      default:
		break;
	    }
	}
	P_RemoveThinker(&floor->thinker);

	S_StartSound(&floor->sector->soundorg, sfx_pstop);
    }

}
