ReadMultiPoint(int iShape)
{
    int i;
    OGRMultiPoint* poMultiPoint = new OGRMultiPoint();
    OGRGeometry* poGeom;

    for (i = iShape + 1; i < nNumShapes; i++)
    {
        poGeom = NULL;
        if (ParentOffset(i) == (unsigned int)iShape)
        {
            if  ( ShapeType(i) == ST_POINT )
                poGeom = ReadPoint(i);
        }
        if ( poGeom )
            poMultiPoint->addGeometryDirectly( poGeom );
    }

    return poMultiPoint;
}
