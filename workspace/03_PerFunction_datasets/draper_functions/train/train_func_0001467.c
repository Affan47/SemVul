gausselim(bmp)
BMDATA *bmp;
{
    word2 *v, *vect, *vectb, *piv;
    unsigned pivot, minc;
    int i;
    int vn, v2n, baslen;
    size_t rk;

    minc = bmp->matinc;
    rk = bmp->rank;
    vn = bmp->vlen;
    v2n = 2*vn;
    baslen = bmp->baslen;

    vect = bmp->bitmat + rk * minc;
    vectb = vect + vn;
    setarr(vectb,vn,0);
    setbit(vectb,rk);

    v = bmp->bitmat;
    piv = bmp->piv;
    for(i=0; i<rk; i++) {
        pivot = piv[i];
        if(testbit(vect,pivot))
            xorarr(vect,v2n,v);
        v += minc;
    }
    for(i=0; i<vn; i++) {
        if(vect[i])
            break;
    }
    if(i == vn)
        return(1);

    for(i=rk; i<=baslen; i++) {
        pivot = piv[i];
        if(testbit(vect,pivot)) {
            piv[i] = piv[rk];
            piv[rk] = pivot;
            break;
        }
    }
    bmp->rank = rk + 1;

    return(0);
}
