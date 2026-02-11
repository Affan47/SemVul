sqliteExprCodeExprList(
  Parse *pParse,
  ExprList *pList,
  int includeTypes
){
  struct ExprList_item *pItem;
  int i, n;
  Vdbe *v;
  if( pList==0 ) return 0;
  v = sqliteGetVdbe(pParse);
  n = pList->nExpr;
  for(pItem=pList->a, i=0; i<n; i++, pItem++){
    sqliteExprCode(pParse, pItem->pExpr);
    if( includeTypes ){
      sqliteVdbeOp3(v, OP_String, 0, 0,
         sqliteExprType(pItem->pExpr)==SQLITE_SO_NUM ? "numeric" : "text",
         P3_STATIC);
    }
  }
  return includeTypes ? n*2 : n;
}
