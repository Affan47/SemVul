xlc_seq_insert_ramp(void)
{
    seq_type arg1 = getseq(xlgaseq());
    long arg2 = getfixnum(xlgafixnum());
    long arg3 = getfixnum(xlgafixnum());
    long arg4 = getfixnum(xlgafixnum());
    long arg5 = getfixnum(xlgafixnum());
    long arg6 = getfixnum(xlgafixnum());
    long arg7 = getfixnum(xlgafixnum());
    long arg8 = getfixnum(xlgafixnum());
    long arg9 = getfixnum(xlgafixnum());

    xllastarg();
    insert_ctrlramp(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    return NIL;
}
