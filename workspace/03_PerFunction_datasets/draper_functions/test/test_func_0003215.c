est_db_fill_key_cache(ESTDB *db){
  const char *kbuf;
  char *msg;
  int i, ksiz, vsiz;
  assert(db);
  vlcurfirst(db->fwmdb);
  for(i = 0; (kbuf = vlcurkeycache(db->fwmdb, &ksiz)) != NULL; i++){
    vsiz = est_idx_vsiz(db->idxdb, kbuf, ksiz);
    cbmapput(db->keycc, kbuf, ksiz, (char *)&vsiz, sizeof(int), TRUE);
    vlcurnext(db->fwmdb);
    if(i % ESTCCCBFREQ == 0){
      msg = cbsprintf("filling the key cache for TF-IDF (%d)", i + 1);
      est_db_inform(db, msg);
      free(msg);
    }
  }
  db->kcmnum = -1;
}
