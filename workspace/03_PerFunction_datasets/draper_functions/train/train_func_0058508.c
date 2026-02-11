EV_MovePoly(line_t * line, byte * args, boolean timesEight, boolean
                    overRide)
{
    int mirror;
    int polyNum;
    polyevent_t *pe;
    polyobj_t *poly;
    angle_t an;

    polyNum = args[0];
    poly = GetPolyobj(polyNum);
    if (poly != NULL)
    {
        if (poly->specialdata && !overRide)
        {
            return false;
        }
    }
    else
    {
        I_Error("EV_MovePoly:  Invalid polyobj num: %d\n", polyNum);
    }
    pe = Z_Malloc(sizeof(polyevent_t), PU_LEVSPEC, 0);
    P_AddThinker(&pe->thinker);
    pe->thinker.function = T_MovePoly;
    pe->polyobj = polyNum;
    if (timesEight)
    {
        pe->dist = args[3] * 8 * FRACUNIT;
    }
    else
    {
        pe->dist = args[3] * FRACUNIT;
    }
    pe->speed = args[1] * (FRACUNIT / 8);
    poly->specialdata = pe;

    an = args[2] * (ANG90 / 64);

    pe->angle = an >> ANGLETOFINESHIFT;
    pe->xSpeed = FixedMul(pe->speed, finecosine[pe->angle]);
    pe->ySpeed = FixedMul(pe->speed, finesine[pe->angle]);
    SN_StartSequence((mobj_t *) & poly->startSpot, SEQ_DOOR_STONE +
                     poly->seqType);

    while ((mirror = GetPolyobjMirror(polyNum)) != 0)
    {
        poly = GetPolyobj(mirror);
        if (poly && poly->specialdata && !overRide)
        {
            break;
        }
        pe = Z_Malloc(sizeof(polyevent_t), PU_LEVSPEC, 0);
        P_AddThinker(&pe->thinker);
        pe->thinker.function = T_MovePoly;
        pe->polyobj = mirror;
        poly->specialdata = pe;
        if (timesEight)
        {
            pe->dist = args[3] * 8 * FRACUNIT;
        }
        else
        {
            pe->dist = args[3] * FRACUNIT;
        }
        pe->speed = args[1] * (FRACUNIT / 8);
        an = an + ANG180;
        pe->angle = an >> ANGLETOFINESHIFT;
        pe->xSpeed = FixedMul(pe->speed, finecosine[pe->angle]);
        pe->ySpeed = FixedMul(pe->speed, finesine[pe->angle]);
        polyNum = mirror;
        SN_StartSequence((mobj_t *) & poly->startSpot, SEQ_DOOR_STONE +
                         poly->seqType);
    }
    return true;
}
