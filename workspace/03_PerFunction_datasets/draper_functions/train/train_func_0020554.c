TriangleArea(float **points, int pDim)
{
    float *p0, *p1, *p2;
    float v0x, v0y;
    float v1x, v1y;
    float a;

    p0 = points[0];
    p1 = points[1];
    p2 = points[2];

    if (pDim == 2)
    {
	v0x = p1[0] - p0[0];
	v0y = p1[1] - p0[1];

	v1x = p2[0] - p0[0];
	v1y = p2[1] - p0[1];

	a = 0.5 * (v0x*v1y - v0y*v1x);
	if (a >= 0) return a;
	else return -a;
    }
    else
    {
	Vector v0, v1, cross;

	vector_subtract((Vector *)p0, (Vector *)p1, &v0);
	vector_subtract((Vector *)p0, (Vector *)p2, &v1);
	vector_cross(&v0, &v1, &cross);
	a = 0.5 * vector_length(&cross);
    }

    if (a >= 0) return a;
    else return -a;
}
