ValidatePolygon(OGRPolygon* poGeom)
{
    int i,j;
    OGRLinearRing* poRing = poGeom->getExteriorRing();
    OGRGeometry* poInteriorRing;

    if (poRing == NULL)
        return FALSE;

    OGRGeometryCollection* poGeometries = NULL;

    if (!ValidateLinearRing(poRing))
    {
        if (poGeom->getNumInteriorRings() > 0)
        {
            poGeometries = new OGRGeometryCollection();
            poGeometries->addGeometryDirectly(poValidGeometry);
        }
    }

    for (i = 0; i < poGeom->getNumInteriorRings(); i++)
    {
        poInteriorRing = poGeom->getInteriorRing(i);
        if (!ValidateLinearRing((OGRLinearRing*)poInteriorRing))
        {
            if (!poGeometries)
            {
                poGeometries = new OGRGeometryCollection();
                poGeometries->addGeometry(poRing);
                for (j = 0; j < i; j++)
                    poGeometries->addGeometry(poGeom->getInteriorRing(j));
            }

            poGeometries->addGeometry(poValidGeometry);
            continue;
        }

        if (poGeometries)
            poGeometries->addGeometry(poInteriorRing);
    }

    if (poGeometries)
    {
        if (poValidGeometry)
            delete poValidGeometry;

        poValidGeometry = poGeometries;
    }

    return (poValidGeometry == NULL);
}
