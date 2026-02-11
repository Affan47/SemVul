objindx(mcmcxdef *mctx, objnum objn)
{
    uint    newsiz;
    uint    avail;
    objdef *objptr;
    uint    cnt;
    prpdef *p;
    uchar  *indp;
    uchar  *indbase;
    uint    icnt;
    uint    first;
    uint    last;
    uint    cur;

    objptr = (objdef *)mcmlck(mctx, objn);
    cnt = objnprop(objptr);
    p = objprp(objptr);
    newsiz = 2 + 4*cnt;

    avail = mcmobjsiz(mctx, objn) - objfree(objptr);


    if (avail < newsiz)
    {
        ushort  need;

        newsiz += 10*4;
        need = newsiz - avail;
        objptr = objexp(mctx, objn, &need);
        p = objprp(objptr);
    }


    indbase = objpfre(objptr);
    for (icnt = 0 ; cnt ; p = objpnxt(p), --cnt, ++icnt)
    {
        uint ofs = (uchar *)p - (uchar *)objptr;

        if (icnt)
        {

            first = 0;
            last = icnt - 1;
            for (;;)
            {
                if (first > last) break;
                cur = first + (last - first)/2;
                indp = indbase + cur*4;
                if (indp[0] == p[0] && indp[1] == p[1])
                    break;
                else if (indp[0] < p[0]
                         || (indp[0] == p[0] && indp[1] < p[1]))
                    first = (cur == first ? first + 1 : cur);
                else
                    last = (cur == last ? last - 1 : cur);
            }


            while (cur < icnt
                   && (indp[0] <= p[0]
                       || (indp[0] == p[0] && indp[1] <= p[1])))
            {
                indp += 4;
                ++cur;
            }


            if (cur < icnt)
                memmove(indp + 4, indp, (size_t)((icnt - cur) * 4));
        }
        else
            indp = indbase;


        indp[0] = p[0];
        indp[1] = p[1];
        oswp2(indp+2, ofs);
    }


    objsflg(objptr, objflg(objptr) | OBJFINDEX);
    mcmtch(mctx, (mcmon)objn);
    mcmunlck(mctx, (mcmon)objn);
}
