sqliteDropIndex(Parse *pParse, SrcList *pName){
  Index *pIndex;
  Vdbe *v;
  sqlite *db = pParse->db;

  if( pParse->nErr || sqlite_malloc_failed ) return;
  assert( pName->nSrc==1 );
  pIndex = sqliteFindIndex(db, pName->a[0].zName, pName->a[0].zDatabase);
  if( pIndex==0 ){
    sqliteErrorMsg(pParse, "no such index: %S", pName, 0);
    goto exit_drop_index;
  }
  if( pIndex->autoIndex ){
    sqliteErrorMsg(pParse, "index associated with UNIQUE "
      "or PRIMARY KEY constraint cannot be dropped", 0);
    goto exit_drop_index;
  }
  if( pIndex->iDb>1 ){
    sqliteErrorMsg(pParse, "cannot alter schema of attached "
       "databases", 0);
    goto exit_drop_index;
  }
#ifndef SQLITE_OMIT_AUTHORIZATION
  {
    int code = SQLITE_DROP_INDEX;
    Table *pTab = pIndex->pTable;
    const char *zDb = db->aDb[pIndex->iDb].zName;
    const char *zTab = SCHEMA_TABLE(pIndex->iDb);
    if( sqliteAuthCheck(pParse, SQLITE_DELETE, zTab, 0, zDb) ){
      goto exit_drop_index;
    }
    if( pIndex->iDb ) code = SQLITE_DROP_TEMP_INDEX;
    if( sqliteAuthCheck(pParse, code, pIndex->zName, pTab->zName, zDb) ){
      goto exit_drop_index;
    }
  }
#endif


  v = sqliteGetVdbe(pParse);
  if( v ){
    static VdbeOpList dropIndex[] = {
      { OP_Rewind,     0, ADDR(9), 0},
      { OP_String,     0, 0,       0},
      { OP_MemStore,   1, 1,       0},
      { OP_MemLoad,    1, 0,       0},
      { OP_Column,     0, 1,       0},
      { OP_Eq,         0, ADDR(8), 0},
      { OP_Next,       0, ADDR(3), 0},
      { OP_Goto,       0, ADDR(9), 0},
      { OP_Delete,     0, 0,       0},
    };
    int base;

    sqliteBeginWriteOperation(pParse, 0, pIndex->iDb);
    sqliteOpenMasterTable(v, pIndex->iDb);
    base = sqliteVdbeAddOpList(v, ArraySize(dropIndex), dropIndex);
    sqliteVdbeChangeP3(v, base+1, pIndex->zName, 0);
    if( pIndex->iDb==0 ){
      sqliteChangeCookie(db, v);
    }
    sqliteVdbeAddOp(v, OP_Close, 0, 0);
    sqliteVdbeAddOp(v, OP_Destroy, pIndex->tnum, pIndex->iDb);
    sqliteEndWriteOperation(pParse);
  }


  if( !pParse->explain ){
    sqliteUnlinkAndDeleteIndex(db, pIndex);
    db->flags |= SQLITE_InternChanges;
  }

exit_drop_index:
  sqliteSrcListDelete(pName);
}
