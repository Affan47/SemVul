nonresdisc(pp,plen,aa,alen,hilf)
word2 *pp, *aa, *hilf;
int plen, alen;
{
    word4 c,v;
    word2 *xx, *yy;
    int k, vlen, xlen, cmp, sign, res;
    unsigned u;

    if(alen > plen)
        alen = modbig(aa,alen,pp,plen,hilf);
    if(!alen)
        return -1;

    xx = hilf;
    hilf += (plen >= alen ? plen : alen) + 2;
    yy = hilf;
    hilf += plen + 2;

    u = 0x1000;
    if(plen == 1 && pp[0] < u) {
        u = pp[0];
    }
    c = random2(u);
    for(k=1; k<=60000; k++,c++) {
        v = c*c;
        vlen = long2big(v,xx);
        cmp = cmparr(aa,alen,xx,vlen);
        if(cmp > 0) {
            xlen = sub1arr(xx,vlen,aa,alen);
            sign = MINUSBYTE;
        }
        else if(cmp < 0) {
            xlen = subarr(xx,vlen,aa,alen);
            sign = 0;
        }
        else
            continue;
        cpyarr(pp,plen,yy);
        res = jacobi(sign,xx,xlen,yy,plen,hilf);
        if(res < 0)
            return c;
        if((k & 0xFF) == 0) {
            if(!rabtest(pp,plen,hilf))
                break;
        }
    }
    return -1;
}
