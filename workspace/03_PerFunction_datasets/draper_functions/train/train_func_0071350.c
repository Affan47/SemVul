utmpx_to_lisp (struct utmpx *utmpx, gcv_object_t *utmpx_o) {
  pushSTACK(check_ut_type_reverse(utmpx->ut_type));
  pushSTACK(safe_to_string(utmpx->ut_user));
  pushSTACK(safe_to_string(utmpx->ut_id));
  pushSTACK(safe_to_string(utmpx->ut_line));
  pushSTACK(L_to_I(utmpx->ut_pid));
#if defined(HAVE_UTMPX_UT_HOST)
  pushSTACK(safe_to_string(utmpx->ut_host));
#else
  pushSTACK(NIL);
#endif
  pushSTACK(sec_usec_number(utmpx->ut_tv.tv_sec,utmpx->ut_tv.tv_usec,1));
  if (utmpx_o) {
    TheStructure(*utmpx_o)->recdata[7] = popSTACK();
    TheStructure(*utmpx_o)->recdata[6] = popSTACK();
    TheStructure(*utmpx_o)->recdata[5] = popSTACK();
    TheStructure(*utmpx_o)->recdata[4] = popSTACK();
    TheStructure(*utmpx_o)->recdata[3] = popSTACK();
    TheStructure(*utmpx_o)->recdata[2] = popSTACK();
    TheStructure(*utmpx_o)->recdata[1] = popSTACK();
    VALUES1(*utmpx_o);
  } else funcall(O(object_posix__make_utmpx),7);
}
