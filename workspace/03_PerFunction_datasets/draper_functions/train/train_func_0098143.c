get_input_bytes(RECSTREAM *rstrm, caddr_t addr,
		int len, bool_t do_align)
{
	int current;

	if (rstrm->in_nonblock) {


		current = (int)(rstrm->in_boundry - rstrm->in_finger);
		if (len > current)
			return (FALSE);
		(void) memcpy(addr, rstrm->in_finger, len);
		rstrm->in_finger += len;
		addr += len;
		return (TRUE);
	}

	while (len > 0) {
		current = (intptr_t)rstrm->in_boundry -
			(intptr_t)rstrm->in_finger;
		if (current == 0) {
			if (!fill_input_buf(rstrm, do_align))
				return (FALSE);
			continue;
		}
		current = (len < current) ? len : current;
		(void) memcpy(addr, rstrm->in_finger, current);
		rstrm->in_finger += current;
		addr += current;
		len -= current;
		do_align = FALSE;
	}
	return (TRUE);
}
