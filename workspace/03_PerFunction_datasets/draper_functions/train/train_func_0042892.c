gdk_gdk_pointer_grab(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj window_scm;
  GdkDrawable* window;
  ScmObj owner_events_scm;
  int owner_events;
  ScmObj event_mask_scm;
  int event_mask;
  ScmObj confine_to_scm;
  GdkDrawable* confine_to;
  ScmObj cursor_scm;
  GdkCursor* cursor;
  ScmObj time__scm;
  u_int time_;
  ScmObj SCM_SUBRARGS[6];
  int SCM_i;
  SCM_ENTER_SUBR("gdk-pointer-grab");
  for (SCM_i=0; SCM_i<6; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  window_scm = SCM_SUBRARGS[0];
  if (!SCM_GDK_DRAWABLE_P(window_scm)) Scm_Error("<gdk-drawable> required, but got %S", window_scm);
  window = SCM_GDK_DRAWABLE(window_scm);
  owner_events_scm = SCM_SUBRARGS[1];
  if (!SCM_BOOLP(owner_events_scm)) Scm_Error("boolean required, but got %S", owner_events_scm);
  owner_events = SCM_BOOL_VALUE(owner_events_scm);
  event_mask_scm = SCM_SUBRARGS[2];
  if (!SCM_INTEGERP(event_mask_scm)) Scm_Error("C integer required, but got %S", event_mask_scm);
  event_mask = Scm_GetInteger(event_mask_scm);
  confine_to_scm = SCM_SUBRARGS[3];
  if (!SCM_GDK_DRAWABLE_P(confine_to_scm)) Scm_Error("<gdk-drawable> required, but got %S", confine_to_scm);
  confine_to = SCM_GDK_DRAWABLE(confine_to_scm);
  cursor_scm = SCM_SUBRARGS[4];
  if (!SCM_GDK_CURSOR_P(cursor_scm)) Scm_Error("<gdk-cursor> required, but got %S", cursor_scm);
  cursor = SCM_GDK_CURSOR(cursor_scm);
  time__scm = SCM_SUBRARGS[5];
  if (!SCM_UINTEGERP(time__scm)) Scm_Error("C integer required, but got %S", time__scm);
  time_ = Scm_GetIntegerU(time__scm);
  {
{
int SCM_RESULT;
SCM_RESULT = gdk_pointer_grab(window, owner_events, event_mask, confine_to, cursor, time_);
SCM_RETURN(Scm_MakeInteger(SCM_RESULT));
}
  }
}
