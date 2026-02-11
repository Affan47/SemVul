showTags(int rid, const char *zNotGlob){
  Stmt q;
  int cnt = 0;
  db_prepare(&q,
    "SELECT tag.tagid, tagname, "
    "       (SELECT uuid FROM blob WHERE rid=tagxref.srcid AND rid!=%d),"
    "       value, datetime(tagxref.mtime,'localtime'), tagtype,"
    "       (SELECT uuid FROM blob WHERE rid=tagxref.origid AND rid!=%d)"
    "  FROM tagxref JOIN tag ON tagxref.tagid=tag.tagid"
    " WHERE tagxref.rid=%d AND tagname NOT GLOB '%q'"
    " ORDER BY tagname /*sort*/", rid, rid, rid, zNotGlob
  );
  while( db_step(&q)==SQLITE_ROW ){
    const char *zTagname = db_column_text(&q, 1);
    const char *zSrcUuid = db_column_text(&q, 2);
    const char *zValue = db_column_text(&q, 3);
    const char *zDate = db_column_text(&q, 4);
    int tagtype = db_column_int(&q, 5);
    const char *zOrigUuid = db_column_text(&q, 6);
    cnt++;
    if( cnt==1 ){
      cgi_printf("<div class=\"section\">Tags And Properties</div>\n"
             "<ul>\n");
    }
    cgi_printf("<li>\n");
    if( tagtype==0 ){
      cgi_printf("<span class=\"infoTagCancelled\">%h</span> cancelled\n",(zTagname));
    }else if( zValue ){
      cgi_printf("<span class=\"infoTag\">%h=%h</span>\n",(zTagname),(zValue));
    }else {
      cgi_printf("<span class=\"infoTag\">%h</span>\n",(zTagname));
    }
    if( tagtype==2 ){
      if( zOrigUuid && zOrigUuid[0] ){
        cgi_printf("inherited from\n");
        hyperlink_to_uuid(zOrigUuid);
      }else{
        cgi_printf("propagates to descendants\n");
      }
#if 0
      if( zValue && fossil_strcmp(zTagname,"branch")==0 ){
        cgi_printf("&nbsp;&nbsp;\n"
               "%zbranch timeline</a>\n",(href("%R/timeline?r=%T",zValue)));
      }
#endif
    }
    if( zSrcUuid && zSrcUuid[0] ){
      if( tagtype==0 ){
        cgi_printf("by\n");
      }else{
        cgi_printf("added by\n");
      }
      hyperlink_to_uuid(zSrcUuid);
      cgi_printf("on\n");
      hyperlink_to_date(zDate,0);
    }
    cgi_printf("</li>\n");
  }
  db_finalize(&q);
  if( cnt ){
    cgi_printf("</ul>\n");
  }
}
