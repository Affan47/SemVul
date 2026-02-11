gtkimcontext_gtk_im_context_set_surrounding(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj context_scm;
  GtkIMContext* context;
  ScmObj text_scm;
  const gchar * text;
  ScmObj len_scm;
  int len;
  ScmObj cursor_index_scm;
  int cursor_index;
  ScmObj SCM_SUBRARGS[4];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-im-context-set-surrounding");
  for (SCM_i=0; SCM_i<4; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  context_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_IM_CONTEXT_P(context_scm)) Scm_Error("<gtk-im-context> required, but got %S", context_scm);
  context = SCM_GTK_IM_CONTEXT(context_scm);
  text_scm = SCM_SUBRARGS[1];
  if (!SCM_STRINGP(text_scm)) Scm_Error("<const-gchar*> required, but got %S", text_scm);
  text = CONST_GCHAR_PTR(text_scm);
  len_scm = SCM_SUBRARGS[2];
  if (!SCM_INTEGERP(len_scm)) Scm_Error("C integer required, but got %S", len_scm);
  len = Scm_GetInteger(len_scm);
  cursor_index_scm = SCM_SUBRARGS[3];
  if (!SCM_INTEGERP(cursor_index_scm)) Scm_Error("C integer required, but got %S", cursor_index_scm);
  cursor_index = Scm_GetInteger(cursor_index_scm);
  {
gtk_im_context_set_surrounding(context, text, len, cursor_index);
SCM_RETURN(SCM_UNDEFINED);
  }
}
