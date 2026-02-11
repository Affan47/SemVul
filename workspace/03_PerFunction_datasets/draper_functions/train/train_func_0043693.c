db_merge(VALUE vself, VALUE vname, VALUE voptions){
  VALUE vdb;
  ESTDBMGR *db;
  vdb = rb_iv_get(vself, VNDATA);
  Data_Get_Struct(vdb, ESTDBMGR, db);
  if(!db->db) rb_raise(rb_eArgError, "invalid argument");
  Check_Type(vname, T_STRING);
  if(!est_mtdb_merge(db->db, StringValuePtr(vname), NUM2INT(voptions))){
    db->ecode = est_mtdb_error(db->db);
    return Qfalse;
  }
  return Qtrue;
}
