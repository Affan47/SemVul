natural_source()
{
	double lgtemp;
	static double vwave;

	if (kt_globals.nper < kt_globals.nopen)
	{
		kt_globals.pulse_shape_a -= kt_globals.pulse_shape_b;
		vwave += kt_globals.pulse_shape_a;
		lgtemp=vwave * 0.028;

		return(lgtemp);
	}
	else
	{
		vwave = 0.0;
		return(0.0);
	}
}
