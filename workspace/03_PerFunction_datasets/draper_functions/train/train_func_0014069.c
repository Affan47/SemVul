doc_attr_names(VALUE vself){
  VALUE vdoc, vnames;
  ESTDOC *doc;
  CBLIST *names;
  vdoc = rb_iv_get(vself, VNDATA);
  Data_Get_Struct(vdoc, ESTDOC, doc);
  names = est_doc_attr_names(doc);
  vnames = cblisttoobj(names);
  cblistclose(names);
  return vnames;
}
