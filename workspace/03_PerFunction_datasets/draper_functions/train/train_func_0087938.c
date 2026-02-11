closeRings()

{
    if( nPointCount < 2 )
        return;

    if( getX(0) != getX(nPointCount-1)
        || getY(0) != getY(nPointCount-1)
        || getZ(0) != getZ(nPointCount-1) )
    {
        OGRPoint oFirstPoint;
        getPoint( 0, &oFirstPoint );
        addPoint( &oFirstPoint );
    }
}
