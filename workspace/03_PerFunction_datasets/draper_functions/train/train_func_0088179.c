GraphCheckPoints(ajint n, const PLFLT *x, const PLFLT *y)
{
    ajint i;

    for(i=0;i<n;i++)
	ajFmtPrint("%d %f %f\n",i,x[i],y[i]);

    return;
}
