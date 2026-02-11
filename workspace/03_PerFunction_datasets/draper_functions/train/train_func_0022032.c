store (zword value)
{
    zbyte variable;

    CODE_BYTE (variable)

    if (variable == 0)
	*--sp = value;
    else if (variable < 16)
	*(fp - variable) = value;
    else {
	zword addr = h_globals + 2 * (variable - 16);
	SET_WORD (addr, value)
    }

}
