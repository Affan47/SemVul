Insideness(const eCoord& pos, const eCoord& direction, const eCoord& lastDirection ) const
{


    eCoord min, max;

    eHalfEdge *run = edge;
    if (!run)
        return -1000000000;

    REAL ret = 1000000000;

    eCoord *last_p = run->Point();
    run = run->next;
    const eHalfEdge *stop = run;

    do
    {
        tASSERT(run && run->Face() == this);
        eCoord *p = run->Point();
        eCoord ed=*last_p - *p;
        eCoord cc= pos - *p;

        REAL val = ed*cc;

        REAL tol = 10 * EPS;
        REAL retDir = direction*ed;
        REAL retLastDir = lastDirection*ed;
        val += tol*(retDir + tol*retLastDir);
        if ( val < ret )
        {
            ret = val;
        }

        last_p = p;
        run = run->next;
    }
    while (run && stop != run);

    return ret;
}
