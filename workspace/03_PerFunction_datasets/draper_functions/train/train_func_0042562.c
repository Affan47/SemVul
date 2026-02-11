zufallsv(double *svblk)
{
    int i;
    extern struct klotz0 klotz0_1;

    svblk[0] = (double)klotz0_1.ptr;
    for (i = 0; i < 607; ++i)
	svblk[i + 1] = klotz0_1.buff[i];
    return 0;
}
