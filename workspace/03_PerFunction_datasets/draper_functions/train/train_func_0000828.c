historydisp()
{
    int k;

    k = SYMbind2(historsym);
    if(k >= 1 && k <= 3)
        k++;
    else if(k >= 'a' || k <= 'c')
        k = 'a' - k - 1;
    else
        k = 2;
    previnput(k);
}
