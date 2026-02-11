halftrace2(_MIPD_ big b,big w)
{
    int i,M;
#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif

    M=mr_mip->M;
    if (M%2==0) return;

    copy(b,mr_mip->w1);
    copy(b,w);

    for (i=1;i<=(M-1)/2;i++)
    {
        modsquare2(_MIPP_ w,w);
        modsquare2(_MIPP_ w,w);
        add2(w,mr_mip->w1,w);
    }
}
