P_MobjThinker(mobj_t * mobj)
{
    mobj_t *onmo;


    if (mobj->momx || mobj->momy || (mobj->flags & MF_SKULLFLY))
    {
        P_XYMovement(mobj);
        if (mobj->thinker.function == (think_t) - 1)
        {
            return;
        }
    }
    if (mobj->flags2 & MF2_FLOATBOB)
    {
        mobj->z = mobj->floorz + FloatBobOffsets[(mobj->health++) & 63];
    }
    else if ((mobj->z != mobj->floorz) || mobj->momz)
    {
        if (mobj->flags2 & MF2_PASSMOBJ)
        {
            if (!(onmo = P_CheckOnmobj(mobj)))
            {
                P_ZMovement(mobj);
            }
            else
            {
                if (mobj->player && mobj->momz < 0)
                {
                    mobj->flags2 |= MF2_ONMOBJ;
                    mobj->momz = 0;
                }
                if (mobj->player && (onmo->player || onmo->type == MT_POD))
                {
                    mobj->momx = onmo->momx;
                    mobj->momy = onmo->momy;
                    if (onmo->z < onmo->floorz)
                    {
                        mobj->z += onmo->floorz - onmo->z;
                        if (onmo->player)
                        {
                            onmo->player->viewheight -=
                                onmo->floorz - onmo->z;
                            onmo->player->deltaviewheight =
                                (VIEWHEIGHT - onmo->player->viewheight) >> 3;
                        }
                        onmo->z = onmo->floorz;
                    }
                }
            }
        }
        else
        {
            P_ZMovement(mobj);
        }
        if (mobj->thinker.function == (think_t) - 1)
        {
            return;
        }
    }


    if (mobj->tics != -1)
    {
        mobj->tics--;

        while (!mobj->tics)
        {
            if (!P_SetMobjState(mobj, mobj->state->nextstate))
            {
                return;
            }
        }
    }
    else
    {
        if (!(mobj->flags & MF_COUNTKILL))
        {
            return;
        }
        if (!respawnmonsters)
        {
            return;
        }
        mobj->movecount++;
        if (mobj->movecount < 12 * 35)
        {
            return;
        }
        if (leveltime & 31)
        {
            return;
        }
        if (P_Random() > 4)
        {
            return;
        }
        P_NightmareRespawn(mobj);
    }
}
