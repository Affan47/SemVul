SqDistance(int mode1, int mode2)
{

	int		k		= 1, s	= 0, p;
	float	dist	= 0, el;
	for(k = 1; k < kp; k++)
	{

		for(p = 0; p < P[k]; p++)
		{
			el    = (modes[mode1*N+p+s]-modes[mode2*N+p+s])/(h[k]*offset[k]);
			dist += el*el;
		}


		s += P[k];
		k++;
	}


	return dist;

}
