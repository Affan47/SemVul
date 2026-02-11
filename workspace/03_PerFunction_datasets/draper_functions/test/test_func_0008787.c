ei_decode_longlong(const char *buf, int *index, EI_LONGLONG *p)
{
    const char *s = buf + *index;
    const char *s0 = s;
    EI_LONGLONG n;
    int arity;

    switch (get8(s)) {
    case ERL_SMALL_INTEGER_EXT:
	n = get8(s);
	break;

    case ERL_INTEGER_EXT:
	n = get32be(s);
	break;

    case ERL_SMALL_BIG_EXT:
	arity = get8(s);
	goto decode_big;

    case ERL_LARGE_BIG_EXT:
	arity = get32be(s);

    decode_big:
	{
	    int sign = get8(s);
	    int i;
	    EI_ULONGLONG u = 0;


	    for (i = 0; i < arity; i++) {
		if (i < 8) {

		    u |= ((EI_ULONGLONG)get8(s)) << (i * 8);
		} else if (get8(s) != 0) {
		    return -1;
		}
	    }


	    if (sign) {
		if (u > MAX_TO_NEGATE) {
		    return -1;
		}
		n = -((EI_LONGLONG) u);
	    } else {
		if (u > MAX_TO_NOT_NEGATE) {
		    return -1;
		}
		n = (EI_LONGLONG) u;
	    }
	}
	break;

    default:
	return -1;
    }

    if (p) *p = n;
    *index += s-s0;

    return 0;
}
