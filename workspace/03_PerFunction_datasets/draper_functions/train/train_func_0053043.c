gdkvisual_gdk_query_depths(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj SCM_SUBRARGS[0];
  int SCM_i;
  SCM_ENTER_SUBR("gdk-query-depths");
  for (SCM_i=0; SCM_i<0; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  {
gint count, *depths; int i; ScmObj h = SCM_NIL, t = SCM_NIL;
  gdk_query_depths(&depths, &count);
  for (i=0; i<count; i++) SCM_APPEND1(h, t, SCM_MAKE_INT(depths[i]));
  SCM_RETURN(h);
  }
}
