z_dec_chk (void)
{
    zword value;

    if (zargs[0] == 0)
	value = --(*sp);
    else if (zargs[0] < 16)
	value = --(*(fp - zargs[0]));
    else {
	zword addr = h_globals + 2 * (zargs[0] - 16);
	LOW_WORD (addr, value)
	value--;
	SET_WORD (addr, value)
    }

    branch ((short) value < (short) zargs[1]);

}
