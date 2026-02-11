sqliteCompleteInsertion(
  Parse *pParse,
  Table *pTab,
  int base,
  char *aIdxUsed,
  int recnoChng,
  int isUpdate,
  int newIdx
){
  int i;
  Vdbe *v;
  int nIdx;
  Index *pIdx;

  v = sqliteGetVdbe(pParse);
  assert( v!=0 );
  assert( pTab->pSelect==0 );
  for(nIdx=0, pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext, nIdx++){}
  for(i=nIdx-1; i>=0; i--){
    if( aIdxUsed && aIdxUsed[i]==0 ) continue;
    sqliteVdbeAddOp(v, OP_IdxPut, base+i+1, 0);
  }
  sqliteVdbeAddOp(v, OP_MakeRecord, pTab->nCol, 0);
  if( newIdx>=0 ){
    sqliteVdbeAddOp(v, OP_Dup, 1, 0);
    sqliteVdbeAddOp(v, OP_Dup, 1, 0);
    sqliteVdbeAddOp(v, OP_PutIntKey, newIdx, 0);
  }
  sqliteVdbeAddOp(v, OP_PutIntKey, base,
    (pParse->trigStack?0:OPFLAG_NCHANGE) |
    (isUpdate?0:OPFLAG_LASTROWID) | OPFLAG_CSCHANGE);
  if( isUpdate && recnoChng ){
    sqliteVdbeAddOp(v, OP_Pop, 1, 0);
  }
}
