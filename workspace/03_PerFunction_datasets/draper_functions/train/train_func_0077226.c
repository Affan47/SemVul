Perl_ckwarn_d(pTHX_ U32 w)
{
    dVAR;

    if (isLEXWARN_off)
	return TRUE;

    return ckwarn_common(w);
}
