zero(flash x)
{
    int i,n;
    mr_small *g;
    if (x==NULL) return;
#ifdef MR_FLASH
    n=mr_lent(x);
#else
    n=(x->len&MR_OBITS);
#endif
    g=x->w;

    for (i=0;i<n;i++)
        g[i]=0;

    x->len=0;
}
