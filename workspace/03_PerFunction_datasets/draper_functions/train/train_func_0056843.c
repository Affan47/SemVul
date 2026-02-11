embIepPhConverge(const ajuint *c, const double *K,
                        ajuint *op, double *pro)
{
    double sum = 0.0;
    double charge;
    double top;
    double mid;
    double bot;
    double H;
    double tph = 1.0;
    double bph = 14.0;

    H = embIepPhToHconc(tph);
    embIepGetProto(K,c,op,H,pro);
    top = embIepGetCharge(c,pro,&sum);
    H = embIepPhToHconc(bph);
    embIepGetProto(K,c,op,H,pro);
    bot = embIepGetCharge(c,pro,&sum);

    if((top>0.0 && bot>0.0) || (top<0.0 && bot<0.0))
	return 0.0;

    while(bph-tph>0.0001)
    {
	mid = ((bph-tph) / 2.0) + tph;
	H = embIepPhToHconc(mid);
	embIepGetProto(K,c,op,H,pro);
	charge = embIepGetCharge(c,pro,&sum);

	if(charge>0.0)
	{
	    tph = mid;
	    continue;
	}

	if(charge<0.0)
	{
	    bph = mid;
	    continue;
	}
	else
	    return mid;
    }

    return tph;
}
