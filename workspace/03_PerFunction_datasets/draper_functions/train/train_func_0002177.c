sendnodecmdetchdoc(ESTMTDB *db, const char *myurl, const char *mylabel,
                               CBMAP *params){
  ESTDOC *doc;
  CBMAP *kwords;
  const char *rp, *uri, *kbuf;
  int id, ksiz;
  id = (rp = cbmapget(params, "id", -1, NULL)) ? atoi(rp) : 0;
  if(!(uri = cbmapget(params, "uri", -1, NULL))) uri = "";
  if(id < 1 && uri[0] == '\0'){
    senderror(400, "Bad Request (the parameters lack)");
    return;
  }
  if(id < 1) id = est_mtdb_uri_to_id(db, uri);
  kwords = NULL;
  if(id > 0){
    kwords = est_mtdb_get_keywords(db, id);
    if(!kwords && (doc = est_mtdb_get_doc(db, id, 0)) != NULL){
      kwords = est_mtdb_etch_doc(db, doc, g_smlrvnum > 0 ? g_smlrvnum : KWORDNUM);
      est_doc_delete(doc);
    }
  }
  if(kwords){
    printf("Content-Type: text/plain; charset=UTF-8\r\n");
    printf("\r\n");
    cbmapiterinit(kwords);
    while((kbuf = cbmapiternext(kwords, &ksiz)) != NULL){
      printf("%s\t%s\n", kbuf, cbmapiterval(kbuf, NULL));
    }
    cbmapclose(kwords);
  } else {
    senderror(400, "Bad Request (maybe, the document does not exist)");
  }
}
