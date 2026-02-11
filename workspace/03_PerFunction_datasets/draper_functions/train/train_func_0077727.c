emit_return_variable(Node *n, SwigType *rt, Wrapper *f) {

  if (!GetFlag(n, "tmap:out:optimal")) {
    if (rt && (SwigType_type(rt) != T_VOID)) {
      SwigType *vt = cplus_value_type(rt);
      SwigType *tt = vt ? vt : rt;
      SwigType *lt = SwigType_ltype(tt);
      String *lstr = SwigType_str(lt, "result");
      if (SwigType_ispointer(lt)) {
        Wrapper_add_localv(f, "result", lstr, "= 0", NULL);
      } else {
        Wrapper_add_local(f, "result", lstr);
      }
      if (vt) {
        Delete(vt);
      }
      Delete(lt);
      Delete(lstr);
    }
  }
}
