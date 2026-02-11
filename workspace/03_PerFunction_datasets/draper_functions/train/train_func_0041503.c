lwgeom_reverse(LWGEOM *lwgeom)
{
	int i;
	LWCOLLECTION *col;

	switch (TYPE_GETTYPE(lwgeom->type))
	{
		case LINETYPE:
			lwline_reverse((LWLINE *)lwgeom);
			return;
		case POLYGONTYPE:
			lwpoly_reverse((LWPOLY *)lwgeom);
			return;
		case MULTILINETYPE:
		case MULTIPOLYGONTYPE:
		case COLLECTIONTYPE:
			col = (LWCOLLECTION *)lwgeom;
			for (i=0; i<col->ngeoms; i++)
				lwgeom_reverse(col->geoms[i]);
			return;
	}
}
