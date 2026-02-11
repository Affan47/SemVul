comWinComplex(const char *win,const char *winsim, ajint lwin,
			  float *ComplexOfWin, ajint jmin, ajint jmax)
{
    ajint j;

    float Ujreal   = 0.0;
    float Ujsim    = 0.0;
    float Ujvalue  = 0.0;
    float WinValue = 1.0;

    for(j=jmin;j<=jmax;j++)
    {
	comCalcUj(lwin,j,win,&Ujreal);
	comCalcUj(lwin,j,winsim,&Ujsim);

	if((Ujreal/Ujsim) > 1.0)
	    Ujvalue = 1.0;
	else
	    Ujvalue = Ujreal/Ujsim;

	WinValue = WinValue*Ujvalue;
    }

    *ComplexOfWin = WinValue;

    return;
}
