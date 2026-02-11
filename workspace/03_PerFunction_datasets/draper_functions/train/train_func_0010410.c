P_FakeZMovement(mobj_t * mo)
{
    int dist;
    int delta;


    mo->z += mo->momz;
    if (mo->flags & MF_FLOAT && mo->target)
    {
        if (!(mo->flags & MF_SKULLFLY) && !(mo->flags & MF_INFLOAT))
        {
            dist =
                P_AproxDistance(mo->x - mo->target->x, mo->y - mo->target->y);
            delta = (mo->target->z + (mo->height >> 1)) - mo->z;
            if (delta < 0 && dist < -(delta * 3))
                mo->z -= FLOATSPEED;
            else if (delta > 0 && dist < (delta * 3))
                mo->z += FLOATSPEED;
        }
    }
    if (mo->player && mo->flags2 & MF2_FLY && !(mo->z <= mo->floorz)
        && leveltime & 2)
    {
        mo->z += finesine[(FINEANGLES / 20 * leveltime >> 2) & FINEMASK];
    }


    if (mo->z <= mo->floorz)
    {
        mo->z = mo->floorz;
        if (mo->momz < 0)
        {
            mo->momz = 0;
        }
        if (mo->flags & MF_SKULLFLY)
        {
            mo->momz = -mo->momz;
        }
        if (mo->info->crashstate && (mo->flags & MF_CORPSE))
        {
            return;
        }
    }
    else if (mo->flags2 & MF2_LOGRAV)
    {
        if (mo->momz == 0)
            mo->momz = -(GRAVITY >> 3) * 2;
        else
            mo->momz -= GRAVITY >> 3;
    }
    else if (!(mo->flags & MF_NOGRAVITY))
    {
        if (mo->momz == 0)
            mo->momz = -GRAVITY * 2;
        else
            mo->momz -= GRAVITY;
    }

    if (mo->z + mo->height > mo->ceilingz)
    {
        if (mo->momz > 0)
            mo->momz = 0;
        mo->z = mo->ceilingz - mo->height;
        if (mo->flags & MF_SKULLFLY)
        {
            mo->momz = -mo->momz;
        }
    }
}
