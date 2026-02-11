regnext(p)
    char_u  *p;
{
    int	    offset;

    if (p == JUST_CALC_SIZE)
	return NULL;

    offset = NEXT(p);
    if (offset == 0)
	return NULL;

    if (OP(p) == BACK)
	return p - offset;
    else
	return p + offset;
}
