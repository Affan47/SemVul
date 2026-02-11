induced_align(int pct)
{
    s_level	*lev = Is_special(&u.uz);
    aligntyp al;

    if (lev && lev->flags.align)
            if(rn2(100) < pct) return(lev->flags.align);

    if(dungeons[u.uz.dnum].flags.align)
            if(rn2(100) < pct) return(dungeons[u.uz.dnum].flags.align);

    al = rn2(3) - 1;
    return(Align2amask(al));
}
