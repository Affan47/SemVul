add_note(const String &s)
{
    if (s.length()) {
	int extra = 1 + (s.back() == '\n' ? 0 : 1);
	if (_binary) {
	    uint32_t marker = htonl((s.length() + extra) | 0x80000000U);
	    ignore_result(fwrite(&marker, 4, 1, _f));
	}
	fputc('#', _f);
	ignore_result(fwrite(s.data(), 1, s.length(), _f));
	if (extra > 1)
	    fputc('\n', _f);
    }
}
