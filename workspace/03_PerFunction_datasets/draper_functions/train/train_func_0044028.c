_ml_P_IO_read (ml_state_t *msp, ml_val_t arg)
{
    int		    fd = REC_SELINT(arg, 0);
    int		    nbytes = REC_SELINT(arg, 1);
    ml_val_t	    vec, res;
    int		    n;

    if (nbytes == 0)
	return ML_string0;


    vec = ML_AllocRaw32 (msp, BYTES_TO_WORDS(nbytes));
    n = read (fd, PTR_MLtoC(char, vec), nbytes);
    if (n < 0)
	return RAISE_SYSERR(msp, n);
    else if (n == 0)
	return ML_string0;

    if (n < nbytes) {

	ML_ShrinkRaw32 (msp, vec, BYTES_TO_WORDS(n));
    }

    SEQHDR_ALLOC (msp, res, DESC_string, vec, n);

    return res;

}
