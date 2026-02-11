bisect_chart(int sortByCkinTime){
  char *zLog = db_lget("bisect-log","");
  Blob log, id;
  Stmt q;
  int cnt = 0;
  blob_init(&log, zLog, -1);
  db_multi_exec(
     "CREATE TEMP TABLE bilog("
     "  seq INTEGER PRIMARY KEY,"
     "  stat TEXT,"
     "  rid INTEGER"
     ");"
  );
  db_prepare(&q, "INSERT OR IGNORE INTO bilog(seq,stat,rid)"
                 " VALUES(:seq,:stat,:rid)");
  while( blob_token(&log, &id) ){
    int rid = atoi(blob_str(&id));
    db_bind_int(&q, ":seq", ++cnt);
    db_bind_text(&q, ":stat", rid>0 ? "GOOD" : "BAD");
    db_bind_int(&q, ":rid", rid>=0 ? rid : -rid);
    db_step(&q);
    db_reset(&q);
  }
  db_bind_int(&q, ":seq", ++cnt);
  db_bind_text(&q, ":stat", "CURRENT");
  db_bind_int(&q, ":rid", db_lget_int("checkout", 0));
  db_step(&q);
  db_finalize(&q);
  db_prepare(&q,
    "SELECT bilog.seq, bilog.stat,"
    "       substr(blob.uuid,1,16), datetime(event.mtime)"
    "  FROM bilog, blob, event"
    " WHERE blob.rid=bilog.rid AND event.objid=bilog.rid"
    "   AND event.type='ci'"
    " ORDER BY %s",
    (sortByCkinTime ? "event.mtime DESC" : "bilog.rowid ASC")
  );
  while( db_step(&q)==SQLITE_ROW ){
    fossil_print("%3d %-7s %s %s\n",
        db_column_int(&q, 0),
        db_column_text(&q, 1),
        db_column_text(&q, 3),
        db_column_text(&q, 2));
  }
  db_finalize(&q);
}
