est_mtdb_search_meta(ESTMTDB **dbs, int dbnum, ESTCOND *cond, int *nump, CBMAP *hints){
  ESTDB **cdbs;
  CBMAP *umap;
  const char *kbuf;
  int i, *rv;
  assert(dbs && dbnum >= 0 && cond && nump);
  cdbs = cbmalloc(dbnum * sizeof(ESTDB *) + 1);
  if(dpisreentrant){
    umap = cbmapopenex(dbnum + 1);
    for(i = 0; i < dbnum; i++){
      if(!cbmapget(umap, (char *)&(dbs[i]), sizeof(ESTDB *), NULL) && !est_mtdb_lock(dbs[i])){
        while(--i >= 0){
          est_mtdb_unlock(dbs[i]);
        }
        free(cdbs);
        est_db_set_ecode(cdbs[i], ESTELOCK);
        cbmapput(hints, "", 0, "0", -1, TRUE);
        *nump = 0;
        return cbmalloc(1);
      }
      cbmapput(umap, (char *)&(dbs[i]), sizeof(ESTDB *), "", 0, FALSE);
      cdbs[i] = dbs[i]->db;
    }
    rv = est_db_search_meta(cdbs, dbnum, cond, nump, hints);
    cbmapiterinit(umap);
    while((kbuf = cbmapiternext(umap, NULL)) != NULL){
      est_mtdb_unlock(*(ESTMTDB **)kbuf);
    }
    cbmapclose(umap);
  } else {
    if(pthread_mutex_lock(&est_global_mutex) != 0){
      *nump = 0;
      return cbmalloc(1);
    }
    for(i = 0; i < dbnum; i++){
      cdbs[i] = dbs[i]->db;
    }
    rv = est_db_search_meta(cdbs, dbnum, cond, nump, hints);
    pthread_mutex_unlock(&est_global_mutex);
  }
  free(cdbs);
  return rv;
}
