lwcollection_segmentize(LWCOLLECTION *collection, uint32 perQuad)
{
        LWCOLLECTION *ocol;
        LWGEOM *tmp;
        LWGEOM **geoms;
        int i;

        LWDEBUG(2, "lwcollection_segmentize called.");

        geoms = lwalloc(sizeof(LWGEOM *)*collection->ngeoms);

        for(i=0; i<collection->ngeoms; i++)
        {
                tmp = collection->geoms[i];
                switch(lwgeom_getType(tmp->type)) {
                case CIRCSTRINGTYPE:
                        geoms[i] = (LWGEOM *)lwcurve_segmentize((LWCIRCSTRING *)tmp, perQuad);
                        break;
                case COMPOUNDTYPE:
                        geoms[i] = (LWGEOM *)lwcompound_segmentize((LWCOMPOUND *)tmp, perQuad);
                        break;
                case CURVEPOLYTYPE:
                        geoms[i] = (LWGEOM *)lwcurvepoly_segmentize((LWCURVEPOLY *)tmp, perQuad);
                        break;
                case COLLECTIONTYPE:
                        geoms[i] = (LWGEOM *)lwcollection_segmentize((LWCOLLECTION *)tmp, perQuad);
                        break;
                default:
                        geoms[i] = lwgeom_clone(tmp);
                        break;
                }
        }
        ocol = lwcollection_construct(COLLECTIONTYPE, collection->SRID, NULL, collection->ngeoms, geoms);
        return ocol;
}
