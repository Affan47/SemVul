sqlite3ExprAssignVarNumber(Parse *pParse, Expr *pExpr){
  Token *pToken;
  if( pExpr==0 ) return;
  pToken = &pExpr->token;
  assert( pToken->n>=1 );
  assert( pToken->z!=0 );
  assert( pToken->z[0]!=0 );
  if( pToken->n==1 ){

    pExpr->iTable = ++pParse->nVar;
  }else if( pToken->z[0]=='?' ){


    int i;
    pExpr->iTable = i = atoi((char*)&pToken->z[1]);
    if( i<1 || i>SQLITE_MAX_VARIABLE_NUMBER ){
      sqlite3ErrorMsg(pParse, "variable number must be between ?1 and ?%d",
          SQLITE_MAX_VARIABLE_NUMBER);
    }
    if( i>pParse->nVar ){
      pParse->nVar = i;
    }
  }else{


    int i, n;
    n = pToken->n;
    for(i=0; i<pParse->nVarExpr; i++){
      Expr *pE;
      if( (pE = pParse->apVarExpr[i])!=0
          && pE->token.n==n
          && memcmp(pE->token.z, pToken->z, n)==0 ){
        pExpr->iTable = pE->iTable;
        break;
      }
    }
    if( i>=pParse->nVarExpr ){
      pExpr->iTable = ++pParse->nVar;
      if( pParse->nVarExpr>=pParse->nVarExprAlloc-1 ){
        pParse->nVarExprAlloc += pParse->nVarExprAlloc + 10;
        pParse->apVarExpr = sqliteReallocOrFree(pParse->apVarExpr,
                       pParse->nVarExprAlloc*sizeof(pParse->apVarExpr[0]) );
      }
      if( !sqlite3MallocFailed() ){
        assert( pParse->apVarExpr!=0 );
        pParse->apVarExpr[pParse->nVarExpr++] = pExpr;
      }
    }
  }
}
