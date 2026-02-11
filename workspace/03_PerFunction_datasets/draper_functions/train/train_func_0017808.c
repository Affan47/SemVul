printPA(POINTARRAY *pa)
{
	int t;
	POINT4D pt;
	char *mflag;


	if ( TYPE_HASM(pa->dims) ) mflag = "M";
	else mflag = "";

	lwnotice("      POINTARRAY%s{", mflag);
	lwnotice("                 ndims=%i,   ptsize=%i",
		TYPE_NDIMS(pa->dims), pointArray_ptsize(pa));
	lwnotice("                 npoints = %i", pa->npoints);

	for (t =0; t<pa->npoints;t++)
	{
		getPoint4d_p(pa, t, &pt);
		if (TYPE_NDIMS(pa->dims) == 2)
		{
			lwnotice("                    %i : %lf,%lf",t,pt.x,pt.y);
		}
		if (TYPE_NDIMS(pa->dims) == 3)
		{
			lwnotice("                    %i : %lf,%lf,%lf",t,pt.x,pt.y,pt.z);
		}
		if (TYPE_NDIMS(pa->dims) == 4)
		{
			lwnotice("                    %i : %lf,%lf,%lf,%lf",t,pt.x,pt.y,pt.z,pt.m);
		}
	}

	lwnotice("      }");
}
