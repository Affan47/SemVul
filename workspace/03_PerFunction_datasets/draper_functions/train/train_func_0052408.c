js_reload_lirc (JSContext *cx, uintN argc, jsval *vp)
{
  se_log_fncall ("reload_lirc");
  se_argc_check_max (0, "reload_lirc");
  gxine_lirc_quit ();
  if (gxine_lirc_thread)
    pthread_join (gxine_lirc_thread, NULL);
  gxine_lirc_start ();
  JS_SET_RVAL (cx, vp, gxine_lirc_thread ? JSVAL_TRUE : JSVAL_FALSE);
  return JS_TRUE;
}
