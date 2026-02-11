z_pull (void)
{
    zword value;

    if (h_version != V6) {

	value = *sp++;

	if (zargs[0] == 0)
	    *sp = value;
	else if (zargs[0] < 16)
	    *(fp - zargs[0]) = value;
	else {
	    zword addr = h_globals + 2 * (zargs[0] - 16);
	    SET_WORD (addr, value)
	}

    } else {

	if (zargc == 1) {

	    zword size;
	    zword addr = zargs[0];

	    LOW_WORD (addr, size)

	    size++;
	    storew (addr, size);

	    addr += 2 * size;
	    LOW_WORD (addr, value)

	} else value = *sp++;

	store (value);

    }

}
