signal_cleanup(void)
{
    t_signal **svec, *sig, *sig2;
    int i;
    while (sig = signal_usedlist)
    {
        signal_usedlist = sig->s_nextused;
        if (!sig->s_isborrowed)
            t_freebytes(sig->s_vec, sig->s_vecsize * sizeof (*sig->s_vec));
        t_freebytes(sig, sizeof *sig);
    }
    for (i = 0; i <= MAXLOGSIG; i++)
        signal_freelist[i] = 0;
    signal_freeborrowed = 0;
}
