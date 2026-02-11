PIT_ChangeSector (mobj_t*   thing)
{
    mobj_t*	mo;

    if (P_ThingHeightClip (thing))
    {

        return true;
    }


    if (thing->health <= 0)
    {

        if(thing->player && thing->subsector->sector->specialdata)
        {
            nofit = true;
            return false;
        }


        A_BodyParts(thing);
        thing->flags &= ~MF_SOLID;
        thing->height = 0;
        thing->radius = 0;


        return true;
    }


    if (thing->flags & MF_DROPPED)
    {
        P_RemoveMobj (thing);


        return true;
    }

    if (! (thing->flags & MF_SHOOTABLE) )
    {

        return true;
    }

    nofit = true;

    if (crushchange && !(leveltime&3) )
    {
        int t;
        S_StartSound(thing, sfx_pcrush);
        P_DamageMobj(thing,NULL,NULL,10);


        mo = P_SpawnMobj (thing->x,
                          thing->y,
                          thing->z + thing->height/2, MT_BLOOD_DEATH);

        t = P_Random();
        mo->momx = (t - P_Random ()) << 12;
        t = P_Random();
        mo->momy = (t - P_Random ()) << 12;
    }


    return true;
}
