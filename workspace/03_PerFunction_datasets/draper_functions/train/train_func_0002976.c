A_InqGrenade(mobj_t* actor)
{
    mobj_t* mo;

    if(!actor->target)
        return;

    A_FaceTarget(actor);

    actor->z += MAXRADIUS;


    actor->angle -= (ANG45 / 32);
    mo = P_SpawnFacingMissile(actor, actor->target, MT_INQGRENADE);
    mo->momz += (9*FRACUNIT);


    actor->angle += (ANG45 / 16);
    mo = P_SpawnFacingMissile(actor, actor->target, MT_INQGRENADE);
    mo->momz += (16*FRACUNIT);

    actor->z -= MAXRADIUS;
}
