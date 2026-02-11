ambiguous_page(void){
  Stmt q;
  const char *zName = P("name");
  const char *zSrc = P("src");
  char *z;

  if( zName==0 || zName[0]==0 || zSrc==0 || zSrc[0]==0 ){
    fossil_redirect_home();
  }
  style_header("Ambiguous Artifact ID");
  cgi_printf("<p>The artifact id <b>%h</b> is ambiguous and might\n"
         "mean any of the following:\n"
         "<ol>\n",(zName));
  z = mprintf("%s", zName);
  canonical16(z, strlen(z));
  db_prepare(&q, "SELECT uuid, rid FROM blob WHERE uuid GLOB '%q*'", z);
  while( db_step(&q)==SQLITE_ROW ){
    const char *zUuid = db_column_text(&q, 0);
    int rid = db_column_int(&q, 1);
    cgi_printf("<li><p><a href=\"%s/%T/%S\">\n"
           "%S</a> -\n",(g.zTop),(zSrc),(zUuid),(zUuid));
    object_description(rid, 0, 0);
    cgi_printf("</p></li>\n");
  }
  cgi_printf("</ol>\n");
  style_footer();
}
