erts_printf_sword(fmtfn_t fn, void *arg, char conv, int pad, int width,
		  ErlPfSWord val)
{
    int count = 0;
    int res;
    int fmt = 0;
    int prec = -1;
    ErlPfUWord ul_val;
    switch (conv) {
    case 'd': fmt |= FMTC_d; break;
    case 'i': fmt |= FMTC_d; break;
    case 'o': fmt |= FMTC_o; break;
    case 'x': fmt |= FMTC_x; break;
    case 'X': fmt |= FMTC_X; break;
    default:
	return -EINVAL;
    }
    if (pad)
	prec = width;
    ul_val = (ErlPfUWord) (val < 0 ? -val : val);
    res = fmt_uword(fn, arg, SIGN(val), ul_val, width, prec, fmt, &count);
    if (res < 0)
	return res;
    return count;
}
