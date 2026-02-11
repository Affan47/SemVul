gtktextbuffer_gtk_text_buffer_insert_interactive_at_cursor(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj buffer_scm;
  GtkTextBuffer* buffer;
  ScmObj text_scm;
  const gchar * text;
  ScmObj len_scm;
  int len;
  ScmObj default_editable_scm;
  int default_editable;
  ScmObj SCM_SUBRARGS[4];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-text-buffer-insert-interactive-at-cursor");
  for (SCM_i=0; SCM_i<4; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  buffer_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_TEXT_BUFFER_P(buffer_scm)) Scm_Error("<gtk-text-buffer> required, but got %S", buffer_scm);
  buffer = SCM_GTK_TEXT_BUFFER(buffer_scm);
  text_scm = SCM_SUBRARGS[1];
  if (!SCM_STRINGP(text_scm)) Scm_Error("<const-gchar*> required, but got %S", text_scm);
  text = CONST_GCHAR_PTR(text_scm);
  len_scm = SCM_SUBRARGS[2];
  if (!SCM_INTEGERP(len_scm)) Scm_Error("C integer required, but got %S", len_scm);
  len = Scm_GetInteger(len_scm);
  default_editable_scm = SCM_SUBRARGS[3];
  if (!SCM_BOOLP(default_editable_scm)) Scm_Error("boolean required, but got %S", default_editable_scm);
  default_editable = SCM_BOOL_VALUE(default_editable_scm);
  {
{
int SCM_RESULT;
SCM_RESULT = gtk_text_buffer_insert_interactive_at_cursor(buffer, text, len, default_editable);
SCM_RETURN(SCM_MAKE_BOOL(SCM_RESULT));
}
  }
}
