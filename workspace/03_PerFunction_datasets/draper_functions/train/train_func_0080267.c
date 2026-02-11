_dxfCompositeField_BoundingBox(Group g, Point *box, Matrix *m, int validity)
{
    Object o;
    int i, j, n=0;
    Point min, max, *p;

    min.x = min.y = min.z = DXD_MAX_FLOAT;
    max.x = max.y = max.z = -DXD_MAX_FLOAT;


    for (i=0; (o=DXGetEnumeratedMember(g, i, NULL)); i++) {


	if (!_dxfBoundingBox(o, box, NULL, validity)) {
	    if (DXGetError()!=ERROR_NONE)
		return NULL;
	    continue;
	}


	if (box)
	{
	    for (j=0, p=box; j<8; j++, p++)
	    {
		if (p->x<min.x) min.x = p->x;  if (p->x>max.x) max.x = p->x;
		if (p->y<min.y) min.y = p->y;  if (p->y>max.y) max.y = p->y;
		if (p->z<min.z) min.z = p->z;  if (p->z>max.z) max.z = p->z;
	    }
	    n++;
	}
    }


    if (box) {
	if (n==0)
	    return NULL;
	for (i=0; i<8; i++)
	{
	    if (m)
	    {
		box[i] = DXApply(DXPt(i&1?max.x:min.x,
				      i&2?max.y:min.y,
				      i&4?max.z:min.z), *m);
	    }
	    else
	    {
		box[i] = DXPt(i&1?max.x:min.x,
			      i&2?max.y:min.y,
			      i&4?max.z:min.z);
	    }
	}
    }

    return (Object) g;
}
