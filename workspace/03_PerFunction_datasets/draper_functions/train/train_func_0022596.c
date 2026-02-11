gtktextbuffer_gtk_text_buffer_remove_tag(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj buffer_scm;
  GtkTextBuffer* buffer;
  ScmObj tag_scm;
  GtkTextTag* tag;
  ScmObj start_scm;
  GtkTextIter* start;
  ScmObj end_scm;
  GtkTextIter* end;
  ScmObj SCM_SUBRARGS[4];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-text-buffer-remove-tag");
  for (SCM_i=0; SCM_i<4; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  buffer_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_TEXT_BUFFER_P(buffer_scm)) Scm_Error("<gtk-text-buffer> required, but got %S", buffer_scm);
  buffer = SCM_GTK_TEXT_BUFFER(buffer_scm);
  tag_scm = SCM_SUBRARGS[1];
  if (!SCM_GTK_TEXT_TAG_P(tag_scm)) Scm_Error("<gtk-text-tag> required, but got %S", tag_scm);
  tag = SCM_GTK_TEXT_TAG(tag_scm);
  start_scm = SCM_SUBRARGS[2];
  if (!SCM_GTK_TEXT_ITER_P(start_scm)) Scm_Error("<gtk-text-iter> required, but got %S", start_scm);
  start = SCM_GTK_TEXT_ITER(start_scm);
  end_scm = SCM_SUBRARGS[3];
  if (!SCM_GTK_TEXT_ITER_P(end_scm)) Scm_Error("<gtk-text-iter> required, but got %S", end_scm);
  end = SCM_GTK_TEXT_ITER(end_scm);
  {
gtk_text_buffer_remove_tag(buffer, tag, start, end);
SCM_RETURN(SCM_UNDEFINED);
  }
}
