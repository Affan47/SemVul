ReducedQuotient (
    FinPowConjCol *     fc,
    Obj                 sc,
    Obj                 w,
    Obj                 u )
{
    Obj                 kind;
    Int                 num;
    Int                 i;
    Obj                 vcw;
    Obj                 vc2;
    Int *               qtr;


    vcw  = SC_CW_VECTOR(sc);
    vc2  = SC_CW2_VECTOR(sc);
    num  = SC_NUMBER_RWS_GENERATORS(sc);
    kind = SC_DEFAULT_TYPE(sc);


    if ( fc->vectorWord( vcw, u, num ) == -1 )  {
        for ( i=num, qtr=(Int*)(ADDR_OBJ(vcw)+1);  0 < i;  i--,qtr++ )
            *qtr = 0;
        return Fail;
    }


    if ( fc->solution( sc, vcw, vc2, fc->collectWord ) == -1 ) {
        for ( i=num, qtr=(Int*)(ADDR_OBJ(vcw)+1);  0<i;  i--,qtr++ )
            *qtr = 0;
        for ( i=num, qtr=(Int*)(ADDR_OBJ(vc2)+1);  0<i;  i--,qtr++ )
            *qtr = 0;
        return ReducedQuotient( fc, sc, w, u );
    }


    u = fc->wordVectorAndClear( kind, vc2, num );


    if ( fc->vectorWord( vcw, w, num ) == -1 )  {
        for ( i = num, qtr = (Int*)(ADDR_OBJ(vcw)+1);  0 < i;  i--, qtr++ )
            *qtr = 0;
        return Fail;
    }


    if ( fc->collectWord( sc, vcw, u ) == -1 ) {
        for ( i = num, qtr = (Int*)(ADDR_OBJ(vcw)+1);  0 < i;  i--, qtr++ )
            *qtr = 0;
        return ReducedQuotient( fc, sc, w, u );
    }


    return fc->wordVectorAndClear( kind, vcw, num );
}
