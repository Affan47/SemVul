Multiplyboundred( Obj     x,
                            Obj     y,
                            UInt    anf,
                            UInt    end,
                            Obj     pcp )
{
    Obj   orders, res, mod, c;
    UInt  i, len, len2, help;

    orders = ELM_PLIST(pcp, PC_ORDERS);
    res = Multiplybound(x,y,anf, end, ELM_PLIST( pcp, PC_DEEP_THOUGHT_POLS) );
    len = LEN_PLIST(res);
    len2 = LEN_PLIST(orders);
    for (i=2; i<=len; i+=2)
        if ( (help=CELM(res, i-1)) <= len2        &&
             ( c=ELM_PLIST( orders, help )) != 0 )
        {
            mod = ModInt( ELM_PLIST(res, i), c );
            SET_ELM_PLIST( res, i, mod);
            CHANGED_BAG(res);
        }
    return res;
}
