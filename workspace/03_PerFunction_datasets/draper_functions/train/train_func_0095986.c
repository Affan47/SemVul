parse_unicode_number(const char* begin, const char* end, int require_prefix, uint32_t& result)
{
    bool allow_lower = (require_prefix == 1);
    if (require_prefix < 0)
	;
    else if (begin + 7 == end && begin[0] == 'u' && begin[1] == 'n' && begin[2] == 'i')
	begin += 3;
    else if (begin + 5 <= end && begin + 7 >= end && begin[0] == 'u')
	begin++;
    else if (begin + 3 <= end && begin + 8 >= end && begin[0] == 'U' && begin[1] == '+')
	begin += 2, allow_lower = true;
    else if (require_prefix > 1)

	return false;

    uint32_t value;
    for (value = 0; begin < end; begin++)
	if (*begin >= '0' && *begin <= '9')
	    value = (value << 4) | (*begin - '0');
	else if (*begin >= 'A' && *begin <= 'F')
	    value = (value << 4) | (*begin - 'A' + 10);
	else if (allow_lower && *begin >= 'a' && *begin <= 'f')
	    value = (value << 4) | (*begin - 'a' + 10);
	else
	    return false;

    if (value > 0
	&& (value <= 0xD7FF || (value >= 0xE000 && value <= 0x10FFFF))) {
	result = value;
	return true;
    } else
	return false;
}
