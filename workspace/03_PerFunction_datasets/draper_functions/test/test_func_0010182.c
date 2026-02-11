T_BuildPillar(pillar_t * pillar)
{
    result_e res1;
    result_e res2;


    res1 = T_MovePlane(pillar->sector, pillar->floorSpeed, pillar->floordest, pillar->crush, 0, pillar->direction);

    res2 = T_MovePlane(pillar->sector, pillar->ceilingSpeed,
                       pillar->ceilingdest, pillar->crush, 1,
                       -pillar->direction);
    if (res1 == RES_PASTDEST && res2 == RES_PASTDEST)
    {
        pillar->sector->specialdata = NULL;
        SN_StopSequence((mobj_t *) & pillar->sector->soundorg);
        P_TagFinished(pillar->sector->tag);
        P_RemoveThinker(&pillar->thinker);
    }
}
