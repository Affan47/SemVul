roundcloser(double d) {
	int n = (int) d;
	double diff = d - (double)n;
	if(diff < 0)
		diff = -diff;
	if(diff >= 0.5)
	{
		if(d < 0)
			n--;
		else
			n++;
	}
	return n;
}
