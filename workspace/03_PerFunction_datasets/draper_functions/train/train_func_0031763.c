doc_score(VALUE vself){
  VALUE vdoc;
  ESTDOC *doc;
  vdoc = rb_iv_get(vself, VNDATA);
  Data_Get_Struct(vdoc, ESTDOC, doc);
  return INT2NUM(est_doc_score(doc));
}
