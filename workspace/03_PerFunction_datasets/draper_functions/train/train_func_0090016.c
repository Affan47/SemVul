RecExpr2 (
    Obj                 rec,
    Expr                expr )
{
    UInt                rnam;
    Obj                 sub;
    Int                 len;
    Expr                tmp;
    Int                 i;


    len = SIZE_EXPR( expr ) / (2*sizeof(Expr));


    for ( i = 1; i <= len; i++ ) {


        tmp = ADDR_EXPR(expr)[2*i-2];
        if ( IS_INTEXPR(tmp) ) {
            rnam = (UInt)INT_INTEXPR(tmp);
        }
        else {
            rnam = RNamObj( EVAL_EXPR(tmp) );
        }


        tmp = ADDR_EXPR(expr)[2*i-1];
        if ( tmp == 0 ) {
            continue;
        }


        else if ( TNUM_EXPR( tmp ) == T_LIST_EXPR ) {
            sub = ListExpr1( tmp );
            AssPRec(rec,rnam,sub);
            ListExpr2( sub, tmp );
        }


        else if ( TNUM_EXPR( tmp ) == T_REC_EXPR ) {
            sub = RecExpr1( tmp );
            AssPRec(rec,rnam,sub);
            RecExpr2( sub, tmp );
        }


        else {
            sub = EVAL_EXPR( tmp );
            AssPRec(rec,rnam,sub);
        }
    }
    SortPRecRNam(rec,0);

}
