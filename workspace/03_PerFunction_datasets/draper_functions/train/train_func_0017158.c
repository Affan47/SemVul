P_TryMove
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )
{
    fixed_t	oldx;
    fixed_t	oldy;
    int		side;
    int		oldside;
    line_t*	ld;

    floatok = false;
    if (!P_CheckPosition (thing, x, y))
	return false;

    if ( !(thing->flags & MF_NOCLIP) )
    {
	if (tmceilingz - tmfloorz < thing->height)
	    return false;

	floatok = true;

	if ( !(thing->flags&MF_TELEPORT)
	     &&tmceilingz - thing->z < thing->height)
	    return false;

	if ( !(thing->flags&MF_TELEPORT)
	     && tmfloorz - thing->z > 24*FRACUNIT )
	    return false;

	if ( !(thing->flags&(MF_DROPOFF|MF_FLOAT))
	     && tmfloorz - tmdropoffz > 24*FRACUNIT )
	    return false;
    }


    P_UnsetThingPosition (thing);

    oldx = thing->x;
    oldy = thing->y;
    thing->floorz = tmfloorz;
    thing->ceilingz = tmceilingz;
    thing->x = x;
    thing->y = y;

    P_SetThingPosition (thing);


    if (! (thing->flags&(MF_TELEPORT|MF_NOCLIP)) )
    {
	while (numspechit--)
	{

	    ld = spechit[numspechit];
	    side = P_PointOnLineSide (thing->x, thing->y, ld);
	    oldside = P_PointOnLineSide (oldx, oldy, ld);
	    if (side != oldside)
	    {
		if (ld->special)
		    P_CrossSpecialLine (ld-lines, oldside, thing);
	    }
	}
    }

    return true;
}
