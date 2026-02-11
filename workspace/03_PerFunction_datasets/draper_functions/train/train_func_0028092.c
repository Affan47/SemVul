parse_integer_portion(const char *s, const char *end, int integer_digits,
		      value_type &ivalue, int &status)
{
    constexpr value_type thresh = integer_traits<value_type>::const_max / 10;
    constexpr int thresh_digit = integer_traits<value_type>::const_max - thresh * 10;
    ivalue = 0;
    while (integer_digits > 0) {
	int digit;
	if (s == end || *s == 'E' || *s == 'e')
	    digit = 0;
	else if (*s >= '0' && *s <= '9') {
	    digit = *s - '0';
	    ++s;
	} else {
	    ++s;
	    continue;
	}
	if (ivalue > thresh || (ivalue == thresh && digit > thresh_digit)) {
	    ivalue = integer_traits<value_type>::const_max;
	    status = NumArg::status_range;
	} else
	    ivalue = 10 * ivalue + digit;
	--integer_digits;
    }
    return s;
}
