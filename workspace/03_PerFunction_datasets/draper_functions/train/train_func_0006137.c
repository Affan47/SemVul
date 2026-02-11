lwpoint_add(const LWPOINT *to, uint32 where, const LWGEOM *what)
{
	LWCOLLECTION *col;
	LWGEOM **geoms;
	int newtype;

	if ( where != -1 && where != 0 )
	{
		lwerror("lwpoint_add only supports 0 or -1 as second argument, got %d", where);
		return NULL;
	}


	geoms = lwalloc(sizeof(LWGEOM *)*2);
	if ( where == -1 )
	{
		geoms[0] = lwgeom_clone((LWGEOM *)to);
		geoms[1] = lwgeom_clone(what);
	}
	else
	{
		geoms[0] = lwgeom_clone(what);
		geoms[1] = lwgeom_clone((LWGEOM *)to);
	}

	lwgeom_dropSRID(geoms[0]);
	lwgeom_drop_bbox(geoms[0]);
	lwgeom_dropSRID(geoms[1]);
	lwgeom_drop_bbox(geoms[1]);


	if ( TYPE_GETTYPE(what->type) == POINTTYPE ) newtype = MULTIPOINTTYPE;
	else newtype = COLLECTIONTYPE;

	col = lwcollection_construct(newtype,
		to->SRID, NULL,
		2, geoms);

	return (LWGEOM *)col;
}
