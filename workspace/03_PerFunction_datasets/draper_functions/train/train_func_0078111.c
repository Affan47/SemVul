tds_convert_datetime4(const TDSCONTEXT * tds_ctx, int srctype, const TDS_CHAR * src, int desttype, CONV_RESULT * cr)
{

	TDS_USMALLINT dt_days, dt_mins;

	char whole_date_string[30];
	TDSDATEREC when;

	switch (desttype) {
	case TDS_CONVERT_CHAR:
	case CASE_ALL_CHAR:
		memset(&when, 0, sizeof(when));

		tds_datecrack(SYBDATETIME4, src, &when);
		tds_strftime(whole_date_string, sizeof(whole_date_string), tds_ctx->locale->date_fmt, &when);

		return string_to_result(whole_date_string, cr);
		break;
	case CASE_ALL_BINARY:
		return binary_to_result(src, sizeof(TDS_DATETIME4), cr);
		break;
	case SYBDATETIME:
		memcpy(&dt_days, src, 2);
		memcpy(&dt_mins, src + 2, 2);
		cr->dt.dtdays = dt_days;
		cr->dt.dttime = (dt_mins * 60) * 300;
		return sizeof(TDS_DATETIME);
		break;
	case SYBDATETIME4:
		memcpy(&cr->dt4, src, sizeof(TDS_DATETIME4));
		return sizeof(TDS_DATETIME4);
		break;

	case SYBUNIQUE:
	case SYBBIT:
	case SYBBITN:
	case SYBINT1:
	case SYBINT2:
	case SYBINT4:
	case SYBINT8:
	case SYBMONEY4:
	case SYBMONEY:
	case SYBNUMERIC:
	case SYBDECIMAL:
	default:
		break;
	}
	return TDS_CONVERT_NOAVAIL;
}
