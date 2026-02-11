activate_label(int i, bool bf) {
  if (!b_attrInit) {
    NCursesApplication* A = NCursesApplication::getApplication();
    if (A) attrset(A->labels());
    b_attrInit = TRUE;
  }
  Soft_Label_Key& K = (*this)[i];
  if (ERR==::slk_set(K.num,bf?K.label:"",K.format))
    Error("slk_set");
  noutrefresh();
}
