testtag_cmd(void){
  const char *zTag;
  const char *zValue;
  int rid;
  int tagtype;
  db_must_be_within_tree();
  if( g.argc!=4 && g.argc!=5 ){
    usage("TAGNAME ARTIFACT-ID ?VALUE?");
  }
  zTag = g.argv[2];
  switch( zTag[0] ){
    case '+':  tagtype = 1;  break;
    case '*':  tagtype = 2;  break;
    case '-':  tagtype = 0;  break;
    default:
      fossil_fatal("tag should begin with '+', '*', or '-'");
      return;
  }
  rid = name_to_rid(g.argv[3]);
  if( rid==0 ){
    fossil_fatal("no such object: %s", g.argv[3]);
  }
  g.markPrivate = content_is_private(rid);
  zValue = g.argc==5 ? g.argv[4] : 0;
  db_begin_transaction();
  tag_insert(zTag, tagtype, zValue, -1, 0.0, rid);
  db_end_transaction(0);
}
