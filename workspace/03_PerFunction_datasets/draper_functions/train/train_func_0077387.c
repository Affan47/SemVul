matchOrderbyToColumn(
  Parse *pParse,
  Select *pSelect,
  ExprList *pOrderBy,
  int iTable,
  int mustComplete
){
  int nErr = 0;
  int i, j;
  ExprList *pEList;

  if( pSelect==0 || pOrderBy==0 ) return 1;
  if( mustComplete ){
    for(i=0; i<pOrderBy->nExpr; i++){ pOrderBy->a[i].done = 0; }
  }
  if( fillInColumnList(pParse, pSelect) ){
    return 1;
  }
  if( pSelect->pPrior ){
    if( matchOrderbyToColumn(pParse, pSelect->pPrior, pOrderBy, iTable, 0) ){
      return 1;
    }
  }
  pEList = pSelect->pEList;
  for(i=0; i<pOrderBy->nExpr; i++){
    Expr *pE = pOrderBy->a[i].pExpr;
    int iCol = -1;
    if( pOrderBy->a[i].done ) continue;
    if( sqliteExprIsInteger(pE, &iCol) ){
      if( iCol<=0 || iCol>pEList->nExpr ){
        sqliteErrorMsg(pParse,
          "ORDER BY position %d should be between 1 and %d",
          iCol, pEList->nExpr);
        nErr++;
        break;
      }
      if( !mustComplete ) continue;
      iCol--;
    }
    for(j=0; iCol<0 && j<pEList->nExpr; j++){
      if( pEList->a[j].zName && (pE->op==TK_ID || pE->op==TK_STRING) ){
        char *zName, *zLabel;
        zName = pEList->a[j].zName;
        assert( pE->token.z );
        zLabel = sqliteStrNDup(pE->token.z, pE->token.n);
        sqliteDequote(zLabel);
        if( sqliteStrICmp(zName, zLabel)==0 ){
          iCol = j;
        }
        sqliteFree(zLabel);
      }
      if( iCol<0 && sqliteExprCompare(pE, pEList->a[j].pExpr) ){
        iCol = j;
      }
    }
    if( iCol>=0 ){
      pE->op = TK_COLUMN;
      pE->iColumn = iCol;
      pE->iTable = iTable;
      pOrderBy->a[i].done = 1;
    }
    if( iCol<0 && mustComplete ){
      sqliteErrorMsg(pParse,
        "ORDER BY term number %d does not match any result column", i+1);
      nErr++;
      break;
    }
  }
  return nErr;
}
