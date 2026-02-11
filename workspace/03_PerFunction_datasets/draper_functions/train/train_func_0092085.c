append_internal_data(const char *s, int len)
{
    if (unlikely(out_of_memory()))
	;
    else if (!_s || _len + len <= _cap)
	append_external_data(s, len);
    else {
	unsigned char *old_s = _s;
	int old_len = _len;
	int old_cap = _cap;

	_s = 0;
	_len = 0;
	_cap = 0;

	if (char *new_s = extend(old_len + len)) {
	    memcpy(new_s, old_s, old_len);
	    memcpy(new_s + old_len, s, len);
	}

	CLICK_LFREE(old_s - MEMO_SPACE, old_cap + MEMO_SPACE);
    }
}
