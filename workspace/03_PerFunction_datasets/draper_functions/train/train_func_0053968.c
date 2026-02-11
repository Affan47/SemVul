a_ck_padany(pTHX_ OP *o) {
 UV hint;

 o = a_old_ck_padany(aTHX_ o);

 hint = a_hint();
 if (hint & A_HINT_DO)
  a_map_store_root(o, o->op_ppaddr, hint);
 else
  a_map_delete(o);

 return o;
}
