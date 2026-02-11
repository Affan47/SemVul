gdkselection_gdk_selection_owner_set(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj owner_scm;
  GdkDrawable* owner;
  ScmObj selection_scm;
  GdkAtom selection;
  ScmObj time__scm;
  u_int time_;
  ScmObj send_event_scm;
  int send_event;
  ScmObj SCM_SUBRARGS[4];
  int SCM_i;
  SCM_ENTER_SUBR("gdk-selection-owner-set");
  for (SCM_i=0; SCM_i<4; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  owner_scm = SCM_SUBRARGS[0];
  if (!SCM_GDK_DRAWABLE_P(owner_scm)) Scm_Error("<gdk-drawable> required, but got %S", owner_scm);
  owner = SCM_GDK_DRAWABLE(owner_scm);
  selection_scm = SCM_SUBRARGS[1];
  if (!SCM_GDK_ATOM_P(selection_scm)) Scm_Error("<gdk-atom> required, but got %S", selection_scm);
  selection = SCM_GDK_ATOM(selection_scm);
  time__scm = SCM_SUBRARGS[2];
  if (!SCM_UINTEGERP(time__scm)) Scm_Error("C integer required, but got %S", time__scm);
  time_ = Scm_GetIntegerU(time__scm);
  send_event_scm = SCM_SUBRARGS[3];
  if (!SCM_BOOLP(send_event_scm)) Scm_Error("boolean required, but got %S", send_event_scm);
  send_event = SCM_BOOL_VALUE(send_event_scm);
  {
{
int SCM_RESULT;
SCM_RESULT = gdk_selection_owner_set(owner, selection, time_, send_event);
SCM_RETURN(SCM_MAKE_BOOL(SCM_RESULT));
}
  }
}
