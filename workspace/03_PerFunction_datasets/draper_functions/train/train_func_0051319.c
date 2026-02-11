setdist(num,denom,a,b)
int num,denom,a,b;
{
	float cor;
	switch (correction)
	{
	case OLSEN:
		cor = parta[a]*parta[b]+
		    partc[a]*partc[b]+
		    partg[a]*partg[b]+
		    partu[a]*partu[b];
		break;

	case JUKES:
		cor = 0.25;
		break;

	case NONE:
		cor = 0.0;
		break;

	default:
		cor = 0.0;
		break;
	};

	if(correction == NONE)
		return(1.0 - (float)num/(float)denom);
	else
		return( -(1.0-cor)*log(1.0 / (1.0-cor)*((float)num/(float)denom-cor)));
}
