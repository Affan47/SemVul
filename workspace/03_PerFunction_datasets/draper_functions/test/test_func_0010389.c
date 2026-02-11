drawCircle(
	int		x,
	int		y,
	int		radius,
	const mrpt::utils::TColor	&color,
	unsigned int	width
	)
{
	if (radius<0) radius=-radius;

	int nSegments;

	if (radius==0)
	{
		nSegments=2;
	}
	else
	{
		nSegments = int(M_2PI * radius);
	}

	int								x1=0,y1=0,x2=0,y2=0;
	double							ang, Aa = M_2PI/(nSegments-1);
	int								i;

	for (i=0,ang=0;i<nSegments;i++,ang+=Aa)
	{
		x2 = round( x + radius * cos(ang) );
		y2 = round( y + radius * sin(ang) );

		if (i>0)
			line( x1, y1,x2, y2,color,width );

		x1 = x2;
		y1 = y2;
	}
}
