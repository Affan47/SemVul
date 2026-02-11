est_mtdb_set_cache_size(ESTMTDB *db, size_t size, int anum, int tnum, int rnum){
  assert(db);
  if(!est_mtdb_lock(db)) return;
  est_db_set_cache_size(db->db, size, anum, tnum, rnum);
  est_mtdb_unlock(db);
}
