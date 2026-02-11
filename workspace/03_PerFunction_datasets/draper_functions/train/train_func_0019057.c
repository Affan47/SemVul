_dxfIsInBox(VectorPart p, POINT_TYPE *pt, int n, int fuzz)
{
    int i;

    if (fuzz)
    {
	for (i = 0; i < n; i++)
	{
	    float f = 0.0001 * (p->max[i] - p->min[i]);
	    if (pt[i] < (p->min[i]-f) ||  pt[i] > (p->max[i]+f)) return 0;
	}
    }
    else
    {
	for (i = 0; i < n; i++)
	    if (pt[i] < p->min[i] ||  pt[i] > p->max[i]) return 0;
    }

    return 1;
}
