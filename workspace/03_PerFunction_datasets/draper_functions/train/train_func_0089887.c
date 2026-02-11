closeRings()

{
    for( int iGeom = 0; iGeom < nGeomCount; iGeom++ )
    {
        if( wkbFlatten(papoGeoms[iGeom]->getGeometryType()) == wkbPolygon )
            ((OGRPolygon *) papoGeoms[iGeom])->closeRings();
    }
}
