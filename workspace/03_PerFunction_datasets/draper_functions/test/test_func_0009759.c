js_pp_video_show (JSContext *cx, uintN argc, jsval *vp)
{
  se_log_fncall_checkinit ("postproc_video_show");
  JSBool ret = post_config_post_chain_window (&chains[POST_CHAIN_VIDEO]);
  if (ret) {
    JS_SET_RVAL (cx, vp, JSVAL_VOID);
  }
  return ret;
}
