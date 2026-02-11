gtkwindow_gtk_window_add_mnemonic(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj window_scm;
  GtkWindow* window;
  ScmObj keyval_scm;
  u_int keyval;
  ScmObj target_scm;
  GtkWidget* target;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-window-add-mnemonic");
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  window_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_WINDOW_P(window_scm)) Scm_Error("<gtk-window> required, but got %S", window_scm);
  window = SCM_GTK_WINDOW(window_scm);
  keyval_scm = SCM_SUBRARGS[1];
  if (!SCM_UINTEGERP(keyval_scm)) Scm_Error("C integer required, but got %S", keyval_scm);
  keyval = Scm_GetIntegerU(keyval_scm);
  target_scm = SCM_SUBRARGS[2];
  if (!SCM_GTK_WIDGET_P(target_scm)) Scm_Error("<gtk-widget> required, but got %S", target_scm);
  target = SCM_GTK_WIDGET(target_scm);
  {
gtk_window_add_mnemonic(window, keyval, target);
SCM_RETURN(SCM_UNDEFINED);
  }
}
