Add(eHalfEdge *e)
{
    tASSERT (e->Point() && e->Next() && e->Next()->Point() && e->Next()->Next() && e->Next()->Next()->Point());

    current++;

    eCoord pos    = *e->Point();

    eCoord offset = ((*e->Next()->Next()->Point() + *e->Next()->Point()) * .5f - pos) * .5f;


    REAL ol = sqrt(offset.NormSquared());
    if (ol > 1)
        offset = offset * (1/ol);

    positions[current] = pos;
    offsets[current]   = offset;
}
