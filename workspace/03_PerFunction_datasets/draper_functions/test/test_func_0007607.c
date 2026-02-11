doc_make_snippet(VALUE vself, VALUE vwords,
                              VALUE vwwidth, VALUE vhwidth, VALUE vawidth){
  VALUE vdoc, vsnippet;
  ESTDOC *doc;
  CBLIST *words;
  int i, len;
  char *snippet;
  vdoc = rb_iv_get(vself, VNDATA);
  Data_Get_Struct(vdoc, ESTDOC, doc);
  Check_Type(vwords, T_ARRAY);
  len = RARRAY_LEN(vwords);
  for(i = 0; i < len; i++){
    Check_Type(rb_ary_entry(vwords, i), T_STRING);
  }
  words = objtocblist(vwords);
  snippet = est_doc_make_snippet(doc, words,
                                 NUM2INT(vwwidth), NUM2INT(vhwidth), NUM2INT(vawidth));
  vsnippet = rb_str_new2(snippet);
  free(snippet);
  cblistclose(words);
  return vsnippet;
}
