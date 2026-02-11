gtktextbuffer_gtk_text_buffer_delete_interactive(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj buffer_scm;
  GtkTextBuffer* buffer;
  ScmObj start_iter_scm;
  GtkTextIter* start_iter;
  ScmObj end_iter_scm;
  GtkTextIter* end_iter;
  ScmObj default_editable_scm;
  int default_editable;
  ScmObj SCM_SUBRARGS[4];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-text-buffer-delete-interactive");
  for (SCM_i=0; SCM_i<4; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  buffer_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_TEXT_BUFFER_P(buffer_scm)) Scm_Error("<gtk-text-buffer> required, but got %S", buffer_scm);
  buffer = SCM_GTK_TEXT_BUFFER(buffer_scm);
  start_iter_scm = SCM_SUBRARGS[1];
  if (!SCM_GTK_TEXT_ITER_P(start_iter_scm)) Scm_Error("<gtk-text-iter> required, but got %S", start_iter_scm);
  start_iter = SCM_GTK_TEXT_ITER(start_iter_scm);
  end_iter_scm = SCM_SUBRARGS[2];
  if (!SCM_GTK_TEXT_ITER_P(end_iter_scm)) Scm_Error("<gtk-text-iter> required, but got %S", end_iter_scm);
  end_iter = SCM_GTK_TEXT_ITER(end_iter_scm);
  default_editable_scm = SCM_SUBRARGS[3];
  if (!SCM_BOOLP(default_editable_scm)) Scm_Error("boolean required, but got %S", default_editable_scm);
  default_editable = SCM_BOOL_VALUE(default_editable_scm);
  {
{
int SCM_RESULT;
SCM_RESULT = gtk_text_buffer_delete_interactive(buffer, start_iter, end_iter, default_editable);
SCM_RETURN(SCM_MAKE_BOOL(SCM_RESULT));
}
  }
}
