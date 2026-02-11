xlc_seq_create(void)
{
    seq_type result;

    xllastarg();
    result = seq_create();
    return cvseq(result);
}
