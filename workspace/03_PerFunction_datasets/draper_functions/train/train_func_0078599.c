VClipPolygon(VPolygon * poly, VPolygon * clipPoly)
{

	int       i;
	VPolygon *p = poly;


	for (i = 0; i < clipPoly->numVtces; ++i) {

		if (p == (VPolygon *) NULL)
			break;

		p = _VClipPolygon(p, &(clipPoly->vertex[i]));

	}

	return p;
}
