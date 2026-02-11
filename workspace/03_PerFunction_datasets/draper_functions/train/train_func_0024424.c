pager_unwritelock(Pager *pPager){
  int rc;
  PgHdr *pPg;
  if( pPager->state<SQLITE_WRITELOCK ) return SQLITE_OK;
  sqlitepager_ckpt_commit(pPager);
  if( pPager->ckptOpen ){
    sqliteOsClose(&pPager->cpfd);
    pPager->ckptOpen = 0;
  }
  if( pPager->journalOpen ){
    sqliteOsClose(&pPager->jfd);
    pPager->journalOpen = 0;
    sqliteOsDelete(pPager->zJournal);
    sqliteFree( pPager->aInJournal );
    pPager->aInJournal = 0;
    for(pPg=pPager->pAll; pPg; pPg=pPg->pNextAll){
      pPg->inJournal = 0;
      pPg->dirty = 0;
      pPg->needSync = 0;
    }
  }else{
    assert( pPager->dirtyFile==0 || pPager->useJournal==0 );
  }
  rc = sqliteOsReadLock(&pPager->fd);
  if( rc==SQLITE_OK ){
    pPager->state = SQLITE_READLOCK;
  }else{


    pPager->state = SQLITE_UNLOCK;
  }
  return rc;
}
