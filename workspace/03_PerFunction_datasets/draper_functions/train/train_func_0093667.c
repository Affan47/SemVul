P_ThingHeightClip(mobj_t * thing)
{
    boolean onfloor;

    onfloor = (thing->z == thing->floorz);

    P_CheckPosition(thing, thing->x, thing->y);


    thing->floorz = tmfloorz;
    thing->ceilingz = tmceilingz;
    thing->floorpic = tmfloorpic;

    if (onfloor)
    {
        if ((thing->z - thing->floorz < 9 * FRACUNIT)
            || (thing->flags & MF_NOGRAVITY))
        {
            thing->z = thing->floorz;
        }
    }
    else
    {
        if (thing->z + thing->height > thing->ceilingz)
            thing->z = thing->ceilingz - thing->height;
    }

    if (thing->ceilingz - thing->floorz < thing->height)
        return false;

    return true;
}
