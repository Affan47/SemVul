T_RotatePoly(polyevent_t * pe)
{
    int absSpeed;
    polyobj_t *poly;

    if (PO_RotatePolyobj(pe->polyobj, pe->speed))
    {
        absSpeed = abs(pe->speed);

        if (pe->dist == -1)
        {
            return;
        }
        pe->dist -= absSpeed;
        if (pe->dist <= 0)
        {
            poly = GetPolyobj(pe->polyobj);
            if (poly->specialdata == pe)
            {
                poly->specialdata = NULL;
            }
            SN_StopSequence((mobj_t *) & poly->startSpot);
            P_PolyobjFinished(poly->tag);
            P_RemoveThinker(&pe->thinker);
        }
        if (pe->dist < absSpeed)
        {
            pe->speed = pe->dist * (pe->speed < 0 ? -1 : 1);
        }
    }
}
