initZlmTable(gint max)
{
	gint l,m;
	if(max<0) max = 0;
	if(z) g_free(z);
	z = g_malloc(sizeof(ZlmTable));
	z->lMax = max;
	z->data = g_malloc((z->lMax+1)*sizeof(Zlm*));
	for( l=0;l<=z->lMax;l++)
		z->data[l] = g_malloc((2*l+1+1)*sizeof(Zlm));

	for( l=0;l<=z->lMax;l++)
		for( m=-l;m<=l;m++)
			z->data[l][m+l] = getZlm(l,m);
}
