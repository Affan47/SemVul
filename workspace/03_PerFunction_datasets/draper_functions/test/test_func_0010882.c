lpc2ref(const float *lpc, float *rfc, int order)
{

    int i,j;
    float f,ai;
    float *vo,*vx;
    float *vn = cst_alloc(float,order);

    i = order-1;
    rfc[i] = ai = lpc[i];
    f = 1-ai*ai;
    i--;

    for (j=0; j<=i; j++)
        rfc[j] = (lpc[j]+((ai*lpc[i-j])))/f;

    vo=rfc;

    for ( ;i>0; )
    {
        ai=vo[i];
        f = 1-ai*ai;
        i--;
	for (j=0; j<=i; j++)
            vn[j] = (vo[j]+((ai*vo[i-j])))/f;

        rfc[i]=vn[i];

        vx = vn;
        vn = vo;
        vo = vx;
    }

    cst_free(vn);

}
