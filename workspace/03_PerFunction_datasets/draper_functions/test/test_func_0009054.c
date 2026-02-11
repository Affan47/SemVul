doc_initialize(int argc, VALUE *argv, VALUE vself){
  VALUE vdraft, vdoc;
  ESTDOC *doc;
  rb_scan_args(argc, argv, "01", &vdraft);
  if(vdraft != Qnil){
    Check_Type(vdraft, T_STRING);
    doc = est_doc_new_from_draft(StringValuePtr(vdraft));
  } else {
    doc = est_doc_new();
  }
  vdoc = Data_Wrap_Struct(cls_doc_data, 0, est_doc_delete, doc);
  rb_iv_set(vself, VNDATA, vdoc);
  return Qnil;
}
