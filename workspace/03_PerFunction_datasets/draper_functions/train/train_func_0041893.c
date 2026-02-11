place_lregion(xchar lx, xchar ly, xchar hx, xchar hy, xchar nlx, xchar nly, xchar nhx, xchar nhy, xchar rtype, d_level *lev)
{
    int trycnt;
    bool oneshot;
    xchar x, y;

    if(!lx)
    {


        if(rtype == LR_BRANCH && nroom)
        {
            place_branch(Is_branchlev(&u.uz), 0, 0);
            return;
        }

        lx = 1; hx = COLNO-1;
        ly = 1; hy = ROWNO-1;
    }


    oneshot = (lx == hx && ly == hy);
    for (trycnt = 0; trycnt < 200; trycnt++)
    {
        x = rn1((hx - lx) + 1, lx);
        y = rn1((hy - ly) + 1, ly);
        if (put_lregion_here(x,y,nlx,nly,nhx,nhy,rtype,oneshot,lev))
                return;
    }


    oneshot = true;
    for (x = lx; x <= hx; x++)
            for (y = ly; y <= hy; y++)
                    if (put_lregion_here(x,y,nlx,nly,nhx,nhy,rtype,oneshot,lev))
                            return;

    impossible("Couldn't place lregion type %d!", rtype);
}
