mr_naf_window(_MIPD_ big x,big x3,int i,int *nbs,int *nzs,int store)
{


    int nb,j,r,biggest;


    nb=mr_testbit(_MIPP_ x3,i)-mr_testbit(_MIPP_ x,i);

    *nbs=1;
    *nzs=0;
    if (nb==0) return 0;
    if (i==0) return nb;

    biggest=2*store-1;

    if (nb>0) r=1;
    else      r=(-1);

    for (j=i-1;j>0;j--)
    {
        (*nbs)++;
        r*=2;
        nb=mr_testbit(_MIPP_ x3,j)-mr_testbit(_MIPP_ x,j);
        if (nb>0) r+=1;
        if (nb<0) r-=1;
        if (abs(r)>biggest) break;
    }

    if (r%2!=0 && j!=0)
    {
        if (nb>0) r=(r-1)/2;
        if (nb<0) r=(r+1)/2;
        (*nbs)--;
    }

    while (r%2==0)
    {
        r/=2;
        (*nzs)++;
        (*nbs)--;
    }
    return r;
}
