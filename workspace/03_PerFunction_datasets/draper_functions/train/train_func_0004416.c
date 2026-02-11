xlgetvalue(LVAL sym)
{
    LVAL val;


    while ((val = xlxgetvalue(sym)) == s_unbound)
        xlunbound(sym);


    return (val);
}
