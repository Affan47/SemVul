has_arc(LWGEOM *geom)
{
        LWCOLLECTION *col;
        int i;

        LWDEBUG(2, "has_arc called.");

        switch(lwgeom_getType(geom->type))
        {
        case POINTTYPE:
        case LINETYPE:
        case POLYGONTYPE:
        case MULTIPOINTTYPE:
        case MULTILINETYPE:
        case MULTIPOLYGONTYPE:
                return 0;
        case CIRCSTRINGTYPE:
                return 1;

        default:
                col = (LWCOLLECTION *)geom;
                for(i=0; i<col->ngeoms; i++)
                {
                        if(has_arc(col->geoms[i]) == 1) return 1;
                }
                return 0;
        }
}
