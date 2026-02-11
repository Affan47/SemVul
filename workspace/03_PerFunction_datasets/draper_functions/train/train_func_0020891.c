ClampMovement( const ePoint* p, eCoord& dir, const eHalfEdge* e )
{
    eHalfEdge* next = e->Next();

    eCoord oppositeEdge = next->Vec();
    eCoord adjacentEdge = e->Vec();


    REAL area = oppositeEdge * adjacentEdge;


    REAL areaChange = dir * oppositeEdge;


    if ( areaChange >= 0 )
        return;


    if ( area + areaChange >= 0 )
        return;


    if ( area < 0 )
    {
        dir = eCoord(0,0);
        return;
    }


    REAL clampFactor = - area / areaChange;
    tASSERT( clampFactor >=0 && clampFactor <= 1 );


    dir = dir * clampFactor;
}
