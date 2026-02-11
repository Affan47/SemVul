gtktextiter_gtk_text_iter_in_range(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj iter_scm;
  GtkTextIter* iter;
  ScmObj start_scm;
  GtkTextIter* start;
  ScmObj end_scm;
  GtkTextIter* end;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-text-iter-in-range");
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  iter_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_TEXT_ITER_P(iter_scm)) Scm_Error("<gtk-text-iter> required, but got %S", iter_scm);
  iter = SCM_GTK_TEXT_ITER(iter_scm);
  start_scm = SCM_SUBRARGS[1];
  if (!SCM_GTK_TEXT_ITER_P(start_scm)) Scm_Error("<gtk-text-iter> required, but got %S", start_scm);
  start = SCM_GTK_TEXT_ITER(start_scm);
  end_scm = SCM_SUBRARGS[2];
  if (!SCM_GTK_TEXT_ITER_P(end_scm)) Scm_Error("<gtk-text-iter> required, but got %S", end_scm);
  end = SCM_GTK_TEXT_ITER(end_scm);
  {
{
int SCM_RESULT;
SCM_RESULT = gtk_text_iter_in_range(iter, start, end);
SCM_RETURN(SCM_MAKE_BOOL(SCM_RESULT));
}
  }
}
