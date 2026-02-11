FreeBondExpr( BondExpr *expr )
  {
    if( expr )
      {
        switch( expr->type )
          {
          case BE_ANDHI:
          case BE_ANDLO:
          case BE_OR:
            FreeBondExpr(expr->bin.lft);
            FreeBondExpr(expr->bin.rgt);
            break;

          case BE_NOT:
            FreeBondExpr(expr->mon.arg);
            break;
          }

        delete expr;
      }
  }
