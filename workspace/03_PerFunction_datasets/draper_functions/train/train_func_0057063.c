sqlite_busy_timeout(sqlite *db, int ms){
  if( ms>0 ){
    sqlite_busy_handler(db, sqliteDefaultBusyCallback, (void*)(long)ms);
  }else{
    sqlite_busy_handler(db, 0, 0);
  }
}
