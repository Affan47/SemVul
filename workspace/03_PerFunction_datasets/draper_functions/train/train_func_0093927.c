gtktextmark_gtk_text_mark_new(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj name_scm;
  const gchar * name;
  ScmObj left_gravity_scm;
  int left_gravity;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-text-mark-new");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  name_scm = SCM_SUBRARGS[0];
  if (!SCM_STRINGP(name_scm)) Scm_Error("<const-gchar*> required, but got %S", name_scm);
  name = CONST_GCHAR_PTR(name_scm);
  left_gravity_scm = SCM_SUBRARGS[1];
  if (!SCM_BOOLP(left_gravity_scm)) Scm_Error("boolean required, but got %S", left_gravity_scm);
  left_gravity = SCM_BOOL_VALUE(left_gravity_scm);
  {
{
GtkTextMark* SCM_RESULT;
SCM_RESULT = gtk_text_mark_new(name, left_gravity);
SCM_RETURN(SCM_MAKE_GTK_TEXT_MARK(SCM_RESULT));
}
  }
}
