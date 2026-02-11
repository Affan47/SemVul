xlc_seq_next(void)
{
    seq_type arg1 = getseq(xlgaseq());
    boolean result;

    xllastarg();
    result = seq_next(arg1);
    return cvboolean(result);
}
