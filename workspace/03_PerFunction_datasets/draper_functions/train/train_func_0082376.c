lwpoly_compute_box2d_p(LWPOLY *poly, BOX2DFLOAT4 *box)
{
	BOX2DFLOAT4 boxbuf;
	uint32 i;

	if ( ! poly->nrings ) return 0;
	if ( ! ptarray_compute_box2d_p(poly->rings[0], box) ) return 0;
	for (i=1; i<poly->nrings; i++)
	{
		if ( ! ptarray_compute_box2d_p(poly->rings[0], &boxbuf) )
			return 0;
		if ( ! box2d_union_p(box, &boxbuf, box) )
			return 0;
	}
	return 1;
}
