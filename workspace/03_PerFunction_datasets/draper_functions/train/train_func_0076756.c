est_db_meta_names(ESTDB *db){
  assert(db);
  if(!db->metacc) est_db_prepare_meta(db);
  return cbmapkeys(db->metacc);
}
