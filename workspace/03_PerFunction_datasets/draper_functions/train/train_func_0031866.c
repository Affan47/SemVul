wiki_filter_mimetypes(const char *zMimetype){
  if( zMimetype!=0 &&
      ( fossil_strcmp(zMimetype, "text/x-markdown")==0
        || fossil_strcmp(zMimetype, "text/plain")==0 )
  ){
    return zMimetype;
  }
  return "text/x-fossil-wiki";
}
