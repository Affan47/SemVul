PIT_RadiusAttack (mobj_t* thing)
{
    fixed_t	dx;
    fixed_t	dy;
    fixed_t	dist;

    if (!(thing->flags & MF_SHOOTABLE) )
	return true;


    if (thing->type == MT_CYBORG
	|| thing->type == MT_SPIDER)
	return true;

    dx = abs(thing->x - bombspot->x);
    dy = abs(thing->y - bombspot->y);

    dist = dx>dy ? dx : dy;
    dist = (dist - thing->radius) >> FRACBITS;

    if (dist < 0)
	dist = 0;

    if (dist >= bombdamage)
	return true;

    if ( P_CheckSight (thing, bombspot) )
    {

	P_DamageMobj (thing, bombspot, bombsource, bombdamage - dist);
    }

    return true;
}
