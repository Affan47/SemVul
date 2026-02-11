round_up(dargp, precision)
	double	*dargp;
	int	precision;
{
	double power = (double) 1;
	int i;

	for(i=0; i<precision; ++i) {
		power /= 10;
	}
	*dargp += (.5 * power);
}
