ValidateGeometryCollection(OGRGeometryCollection* poGeom)
{
    int i, j;
    OGRGeometry* poGeometry;
    OGRGeometryCollection* poGeometries = NULL;

    for (i = 0; i < poGeom->getNumGeometries(); i++)
    {
        poGeometry = poGeom->getGeometryRef(i);

        if (!ValidateGeometry(poGeometry))
        {

            if (!poGeometries)
            {
                poGeometries = new OGRGeometryCollection();
                for (j = 0; j < i; j++)
                    poGeometries->addGeometry(poGeom->getGeometryRef(j));
            }

            if (poValidGeometry)
                poGeometries->addGeometry(poValidGeometry);
            continue;
        }

        if (poGeometries)
            poGeometries->addGeometry(poGeometry);
    }

    if (poGeometries)
    {
        if (poValidGeometry)
            delete poValidGeometry;

        poValidGeometry = poGeometries;
    }

    return (poValidGeometry == NULL);
}
