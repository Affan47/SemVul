set_precision(const char *optarg)
{
    char *ptr1 = 0;
    char *ptr2 = 0;
    int flt_digits = FLT_DIGITS;
    int dbl_digits = DBL_DIGITS;

    if (optarg != 0 && (int) strlen(optarg) > 0 && optarg[0] != ',') {
        flt_digits = (int)strtol(optarg, &ptr1, 10);
	float_precision_specified = 1;
    }

    if (flt_digits < 1 || flt_digits > 20) {
	error("unreasonable value for float significant digits: %d",
	      flt_digits);
    }
    if (ptr1 && *ptr1 == ',') {
	dbl_digits = (int) strtol(ptr1+1, &ptr2, 10);
	double_precision_specified = 1;
	if (ptr2 == ptr1+1 || dbl_digits < 1 || dbl_digits > 20) {
	    error("unreasonable value for double significant digits: %d",
		  dbl_digits);
	}
    }
    set_formats(flt_digits, dbl_digits);
}
