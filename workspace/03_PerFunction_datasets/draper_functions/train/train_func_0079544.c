CreateTable2(gint N)
{
	gdouble** T;
	gint i;
	gint j;

	T = g_malloc(N*sizeof(gdouble*)) ;
	for(i=0;i<N;i++)
	{
		T[i] = g_malloc(N*sizeof(gdouble));
		for(j=0;j<N;j++) T[i][j] = 0.0;
	}

	return T;
}
