expires_sec(double days_till_expire) {
	time_t result=time(NULL)+(time_t)(60*60*24*days_till_expire);
	struct tm* tms=gmtime(&result);
	if(!tms)
		throw Exception(DATE_RANGE_EXCEPTION_TYPE,
			0,
			"bad expires time (seconds from epoch=%u)", result);
	return result;
}
