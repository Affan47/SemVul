_ml_Sock_recv (ml_state_t *msp, ml_val_t arg)
{
    int		sock = REC_SELINT(arg, 0);
    int		nbytes = REC_SELINT(arg, 1);
    int		flag = 0;
    ml_val_t	vec, res;
    int		n;

    if (REC_SEL(arg, 2) == ML_true) flag |= MSG_OOB;
    if (REC_SEL(arg, 3) == ML_true) flag |= MSG_PEEK;


    vec = ML_AllocRaw32 (msp, BYTES_TO_WORDS(nbytes));

    n = recv (sock, PTR_MLtoC(char, vec), nbytes, flag);

    if (n < 0)
	return RAISE_SYSERR(msp, sts);
    else if (n == 0)
	return ML_string0;

    if (n < nbytes) {

	ML_ShrinkRaw32 (msp, vec, BYTES_TO_WORDS(n));
    }

    SEQHDR_ALLOC (msp, res, DESC_string, vec, n);

    return res;

}
