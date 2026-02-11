InsideFace(float  x,	  float y,
	   int    face,   float *positions,
	   int    *faces, int   nF,
	   int    *loops, int   nL,
	   int    *edges, int   nE,
	   MinMax *loopMM)
{
    int     l;
    int     ls = faces[face];
    int     le = (face == nF-1) ? nL : faces[face+1];
    MinMax *lmm;
    int     knt = 0;

    for (l = ls, lmm = loopMM + ls; l < le; l++, lmm++)
    {
	int     e;
	int     es = loops[l];
	int     ee = (l == nL-1) ? nE : loops[l+1];

	if (x >= lmm->x && x <= lmm->X &&
	    y >= lmm->y && y <= lmm->Y)
	{
	    int    q = edges[es];
	    float *ppos, *qpos = positions+(q<<1);
	    float *t, *b, intercept, d;

	    for (e = es; e < ee; e++)
	    {

		ppos = qpos;

		q    = (e == ee-1) ? edges[es] : edges[e+1];
		qpos = positions+(q<<1);

		if      (qpos[1] > ppos[1]) t = qpos, b = ppos;
		else if (qpos[1] < ppos[1]) t = ppos, b = qpos;
		else continue;

		if (t[1] <  y) continue;
		if (b[1] >= y) continue;
		if (t[0] < x && b[0] < x) continue;
		if (t[0] > x && b[0] > x)
		{
		    knt++;
		    continue;
		}

		d = (y - t[1]) / (b[1] - t[1]);
		intercept = t[0] + d*(b[0] - t[0]);

		if (intercept > x) knt++;
	    }
	}
    }

    return knt & 0x1;
}
