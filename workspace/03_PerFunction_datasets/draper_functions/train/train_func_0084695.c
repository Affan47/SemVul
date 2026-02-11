ft_primary(fits)
	FITSHead	fits;
{
	FITSHead prim;
        int             one = 1;

    prim = ft_headcopy(fits);

    ft_cardfmt(ft_cardnth(prim, 1)
		, "SIMPLE", 0, FT_LOGICAL, &one, 0, FT_Comment);

    ft_headdel(prim, "EXTVER", 0);
    ft_headdel(prim, "GCOUNT", 0);
    ft_headdel(prim, "PCOUNT", 0);
    ft_headdel(prim, "EXTEND", 0);
    ft_headdel(prim, "NEXTEND", 0);
    ft_headdel(prim, "INHERIT", 0);

    return prim;
}
