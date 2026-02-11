parse_saturating(const String &str, uint32_t &iresult,
				       uint32_t &fresult, const ArgContext &)
{
    value_type ivalue;
    uint32_t fvalue;
    const char *end = parse_decimal_fraction(str.begin(), str.end(),
					     false, exponent_delta,
					     ivalue, fraction_digits, fvalue, status);
    if (end != str.end())
	status = status_inval;
    if (status && status != status_range)
	return false;
    if (uint32_t(ivalue) != ivalue)
	status = status_range;
    if (status == status_range) {
	iresult = integer_traits<uint32_t>::const_max;
	fresult = exp10val[fraction_digits] - 1;
    } else {
	iresult = ivalue;
	fresult = fvalue;
    }
    return true;
}
