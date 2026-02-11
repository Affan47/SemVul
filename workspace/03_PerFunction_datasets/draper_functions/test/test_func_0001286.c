cs_wclear (CS_INT mark, CS_INT lemax, CS_INT *w, CS_INT n)
{
    CS_INT k ;
    if (mark < 2 || (mark + lemax < 0))
    {
        for (k = 0 ; k < n ; k++) if (w [k] != 0) w [k] = 1 ;
        mark = 2 ;
    }
    return (mark) ;
}
