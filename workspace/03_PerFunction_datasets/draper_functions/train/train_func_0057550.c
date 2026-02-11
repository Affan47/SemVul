setPolygon(Polygon* pdata, size_t poly)
    {
        OgreAssert(poly < getPolygonCount(), "Search position out of range" );
        OgreAssert(pdata != NULL, "Polygon is NULL" );

        if (pdata != mPolygons[poly])
        {

            freePolygon(mPolygons[ poly ]);


            mPolygons[poly] = pdata;
        }
    }
