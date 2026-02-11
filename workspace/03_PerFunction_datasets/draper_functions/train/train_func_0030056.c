content_mark_available(int rid){
  Bag pending;
  static Stmt q;
  if( bag_find(&contentCache.available, rid) ) return;
  bag_init(&pending);
  bag_insert(&pending, rid);
  while( (rid = bag_first(&pending))!=0 ){
    bag_remove(&pending, rid);
    bag_remove(&contentCache.missing, rid);
    bag_insert(&contentCache.available, rid);
    db_static_prepare(&q, "SELECT rid FROM delta WHERE srcid=:rid");
    db_bind_int(&q, ":rid", rid);
    while( db_step(&q)==SQLITE_ROW ){
      int nx = db_column_int(&q, 0);
      bag_insert(&pending, nx);
    }
    db_reset(&q);
  }
  bag_clear(&pending);
}
