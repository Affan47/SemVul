complex_out (double x, double y)


{	if (fraceps>0)
	{   if (!frac_out(x)) goto one;
		if (y!=0.0)
		{	if (y>0) output1hold(-1,"+");
			else if (y<0) output1hold(-1,"-");
			if (!frac_out0(fabs(y))) goto two;
		}
	}
	else
	{   one :
		if ((fabs(x)>maxexpo || fabs(x)<minexpo) && x!=0.0)
		output1hold(0,expoformat,x);
		else output1hold(0,fixedformat,x);
		if (y>=0) output1hold(-1,"+");
		else output1hold(-1,"-");
		y=fabs(y);
		two :
		if ((y>maxexpo || y<minexpo) && y!=0.0)
		output1hold(-1,expoformat,y);
		else output1hold(-1,fixedformat,y);
	}
	output1hold(outputlength*2,"i ");
}
