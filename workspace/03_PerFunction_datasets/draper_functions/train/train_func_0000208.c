lwline_serialize_buf(LWLINE *line, uchar *buf, size_t *retsize)
{
	char hasSRID;
	uchar *loc;
	int ptsize;
	size_t size;

	LWDEBUGF(2, "lwline_serialize_buf(%p, %p, %p) called",
		line, buf, retsize);

	if (line == NULL)
		lwerror("lwline_serialize:: given null line");

	if ( TYPE_GETZM(line->type) != TYPE_GETZM(line->points->dims) )
		lwerror("Dimensions mismatch in lwline");

	ptsize = pointArray_ptsize(line->points);

	hasSRID = (line->SRID != -1);

	buf[0] = (uchar) lwgeom_makeType_full(
		TYPE_HASZ(line->type), TYPE_HASM(line->type),
		hasSRID, LINETYPE, line->bbox ? 1 : 0);
	loc = buf+1;

	LWDEBUGF(3, "lwline_serialize_buf added type (%d)", line->type);

	if (line->bbox)
	{
		memcpy(loc, line->bbox, sizeof(BOX2DFLOAT4));
		loc += sizeof(BOX2DFLOAT4);

		LWDEBUG(3, "lwline_serialize_buf added BBOX");
	}

	if (hasSRID)
	{
		memcpy(loc, &line->SRID, sizeof(int32));
		loc += sizeof(int32);

		LWDEBUG(3, "lwline_serialize_buf added SRID");
	}

	memcpy(loc, &line->points->npoints, sizeof(uint32));
	loc += sizeof(uint32);

	LWDEBUGF(3, "lwline_serialize_buf added npoints (%d)",
		line->points->npoints);


	size = line->points->npoints*ptsize;
	memcpy(loc, getPoint_internal(line->points, 0), size);
	loc += size;

	LWDEBUGF(3, "lwline_serialize_buf copied serialized_pointlist (%d bytes)",
		ptsize * line->points->npoints);

	if (retsize) *retsize = loc-buf;


	LWDEBUGF(3, "lwline_serialize_buf returning (loc: %p, size: %d)",
		loc, loc-buf);
}
