find_left(const String &x, int start) const
{
    if (start < 0)
	start = 0;
    if (x.length() == 0 && start <= length())
	return start;
    if (start + x.length() > length())
	return -1;
    const char *pos = _r.data + start;
    const char *end_pos = _r.data + length() - x.length() + 1;
    char first_c = (unsigned char) x[0];
    while (pos < end_pos) {
	pos = (const char *) memchr(pos, first_c, end_pos - pos);
	if (!pos)
	    break;
	if (memcmp(pos + 1, x.data() + 1, x.length() - 1) == 0)
	    return pos - _r.data;
	++pos;
    }
    return -1;
}
