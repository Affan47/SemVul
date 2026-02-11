gb_rules_get_next_accrual (gbSeries  series,
			   gbDate    idate,
			   gbDate    rdate,
			   gbDate    mdate,
			   gbDate   *a2date )
{
	gbDate   a1date;
	gint     total_months, accrual_step_months=6;
	gbStatus rval;

	total_months =   rdate - idate;

	if ( total_months < 0 ) {
		*a2date = 0;
		return GB_OK;
	}

	rval= gb_rules_get_last_accrual( series, idate, rdate, mdate, &a1date );
	if ( rval != GB_OK ) {
		return rval;
	}

	switch (series) {

	case GB_SERIES_EE:
		if ( idate >= GB_DATE(MAY,1997) ) {
			accrual_step_months = 1;
		}
		else {
			if ( (idate >= GB_DATE(MAR,1993)) && (idate <= GB_DATE(APR,1995))
			     && ( total_months < 60 ) ) {
				accrual_step_months = 1;
			}
			else {
				accrual_step_months = 6;
			}
		}
		break;

	case GB_SERIES_S:
		accrual_step_months = 6;
		break;

	case GB_SERIES_I:
		accrual_step_months = 6;
		break;

	case GB_SERIES_E:
		accrual_step_months = 6;
		break;

	default:
		return GB_ERROR_BAD_SERIES;
	}

	if ( (a1date + accrual_step_months) >= mdate ) {
		*a2date = mdate;
	}
	else {
		*a2date = a1date + accrual_step_months;
	}

	return GB_OK;
}
