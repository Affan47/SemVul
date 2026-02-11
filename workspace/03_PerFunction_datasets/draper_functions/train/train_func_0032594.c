tweak_generic_double(struct cli *cli, const struct parspec *par,
    const char *arg)
{
	volatile double *dest;
	double u;

	dest = par->priv;
	if (arg != NULL) {
		u = strtod(arg, NULL);
		if (u < par->min) {
			VCLI_Out(cli,
			    "Must be greater or equal to %.g\n",
				 par->min);
			VCLI_SetResult(cli, CLIS_PARAM);
			return;
		}
		if (u > par->max) {
			VCLI_Out(cli,
			    "Must be less than or equal to %.g\n",
				 par->max);
			VCLI_SetResult(cli, CLIS_PARAM);
			return;
		}
		*dest = u;
	} else
		VCLI_Out(cli, "%f", *dest);
}
