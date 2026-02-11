annual_year_basis (GnmValue const *value_date, GOBasisType basis,
		   GODateConventions const *date_conv)
{
        GDate    date;

	switch (basis) {
	case GO_BASIS_MSRB_30_360:
	        return 360;
	case GO_BASIS_ACT_ACT:
		if (!datetime_value_to_g (&date, value_date, date_conv))
		        return -1;
		return g_date_is_leap_year (g_date_get_year (&date))
			? 366 : 365;
	case GO_BASIS_ACT_360:
	        return 360;
	case GO_BASIS_ACT_365:
	        return 365;
	case GO_BASIS_30E_360:
	        return 360;
	default:
	        return -1;
	}
}
