gdk_gdk_screen_height_mm(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj SCM_SUBRARGS[0];
  int SCM_i;
  SCM_ENTER_SUBR("gdk-screen-height-mm");
  for (SCM_i=0; SCM_i<0; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  {
{
int SCM_RESULT;
SCM_RESULT = gdk_screen_height_mm();
SCM_RETURN(Scm_MakeInteger(SCM_RESULT));
}
  }
}
