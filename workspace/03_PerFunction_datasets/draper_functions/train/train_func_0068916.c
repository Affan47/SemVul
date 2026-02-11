swap(struct xfield *xf, float *den, int a, int b) {
    if (ABS(den[a]) > ABS(den[b])) {
	{float t; t=den[a]; den[a]=den[b]; den[b]=t;}
	{Vector t; t=xf->d[a]; xf->d[a]=xf->d[b]; xf->d[b]=t;}
	{int t; t=xf->k[a]; xf->k[a]=xf->k[b]; xf->k[b]=t;}
	{int t; t=xf->s[a]; xf->s[a]=xf->s[b]; xf->s[b]=t;}
	{int t; t=xf->ck[a]; xf->ck[a]=xf->ck[b]; xf->ck[b]=t;}
	{int t; t=xf->cs[a]; xf->cs[a]=xf->cs[b]; xf->cs[b]=t;}
    }
}
