sqliteBtreeOpen(
  const char *zFilename,
  int omitJournal,
  int nCache,
  Btree **ppBtree
){
  Btree *pBt;
  int rc;


  assert( sizeof(u32)==4 );
  assert( sizeof(u16)==2 );
  assert( sizeof(Pgno)==4 );
  assert( sizeof(PageHdr)==8 );
  assert( sizeof(CellHdr)==12 );
  assert( sizeof(FreeBlk)==4 );
  assert( sizeof(OverflowPage)==SQLITE_USABLE_SIZE );
  assert( sizeof(FreelistInfo)==OVERFLOW_SIZE );
  assert( sizeof(ptr)==sizeof(char*) );
  assert( sizeof(uptr)==sizeof(ptr) );

  pBt = sqliteMalloc( sizeof(*pBt) );
  if( pBt==0 ){
    *ppBtree = 0;
    return SQLITE_NOMEM;
  }
  if( nCache<10 ) nCache = 10;
  rc = sqlitepager_open(&pBt->pPager, zFilename, nCache, EXTRA_SIZE,
                        !omitJournal);
  if( rc!=SQLITE_OK ){
    if( pBt->pPager ) sqlitepager_close(pBt->pPager);
    sqliteFree(pBt);
    *ppBtree = 0;
    return rc;
  }
  sqlitepager_set_destructor(pBt->pPager, pageDestructor);
  pBt->pCursor = 0;
  pBt->page1 = 0;
  pBt->readOnly = sqlitepager_isreadonly(pBt->pPager);
  pBt->pOps = &sqliteBtreeOps;
  *ppBtree = pBt;
  return SQLITE_OK;
}
