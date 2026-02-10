sqlite3Expr(int op, Expr *pLeft, Expr *pRight, const Token *pToken){
  Expr *pNew;
  pNew = sqliteMalloc( sizeof(Expr) );
  if( pNew==0 ){


    sqlite3ExprDelete(pLeft);
    sqlite3ExprDelete(pRight);
    return 0;
  }
  pNew->op = op;
  pNew->pLeft = pLeft;
  pNew->pRight = pRight;
  pNew->iAgg = -1;
  if( pToken ){
    assert( pToken->dyn==0 );
    pNew->span = pNew->token = *pToken;
  }else if( pLeft ){
    if( pRight ){
      sqlite3ExprSpan(pNew, &pLeft->span, &pRight->span);
      if( pRight->flags & EP_ExpCollate ){
        pNew->flags |= EP_ExpCollate;
        pNew->pColl = pRight->pColl;
      }
    }
    if( pLeft->flags & EP_ExpCollate ){
      pNew->flags |= EP_ExpCollate;
      pNew->pColl = pLeft->pColl;
    }
  }
  return pNew;
}
