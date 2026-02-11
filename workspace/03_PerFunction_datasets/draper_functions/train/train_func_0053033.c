test_ticket_rebuild(void){
  db_find_and_open_repository(0, 0);
  if( g.argc!=3 ) usage("TICKETID|all");
  if( fossil_strcmp(g.argv[2], "all")==0 ){
    ticket_rebuild();
  }else{
    const char *zUuid;
    zUuid = db_text(0, "SELECT substr(tagname,5) FROM tag"
                       " WHERE tagname GLOB 'tkt-%q*'", g.argv[2]);
    if( zUuid==0 ) fossil_fatal("no such ticket: %s", g.argv[2]);
    ticket_rebuild_entry(zUuid);
  }
}
