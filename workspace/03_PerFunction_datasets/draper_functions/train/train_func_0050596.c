parse_columns(const String &s, int &which, int &count)
{
    const char *slash = find(s, '/');
    if (!cp_integer(s.substring(s.begin(), slash), &which)
	|| !cp_integer(s.substring(slash + 1, s.end()), &count)
	|| which <= 0 || which > count) {
	which = count = 1;
	return false;
    } else
	return true;
}
