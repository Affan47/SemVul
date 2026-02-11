mem_undiff (zbyte *diff, long diff_length, zbyte *dest)
{
    zbyte c;

    while (diff_length) {
	c = *diff++;
	diff_length--;
	if (c == 0) {
	    unsigned runlen;

	    if (!diff_length)
		return;
	    runlen = *diff++;
	    diff_length--;
	    if (runlen & 0x80) {
		if (!diff_length)
		    return;
		c = *diff++;
		diff_length--;
		runlen = (runlen & 0x7f) | (((unsigned) c) << 7);
	    }

	    dest += runlen + 1;
	} else {
	    *dest++ ^= c;
	}
    }
}
