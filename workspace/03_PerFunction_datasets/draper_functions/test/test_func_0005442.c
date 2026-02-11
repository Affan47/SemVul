gtkbindings_gtk_bindings_activate(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj object_scm;
  GtkObject* object;
  ScmObj keyval_scm;
  u_int keyval;
  ScmObj modifiers_scm;
  int modifiers;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-bindings-activate");
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  object_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_OBJECT_P(object_scm)) Scm_Error("<gtk-object> required, but got %S", object_scm);
  object = SCM_GTK_OBJECT(object_scm);
  keyval_scm = SCM_SUBRARGS[1];
  if (!SCM_UINTEGERP(keyval_scm)) Scm_Error("C integer required, but got %S", keyval_scm);
  keyval = Scm_GetIntegerU(keyval_scm);
  modifiers_scm = SCM_SUBRARGS[2];
  if (!SCM_INTEGERP(modifiers_scm)) Scm_Error("C integer required, but got %S", modifiers_scm);
  modifiers = Scm_GetInteger(modifiers_scm);
  {
{
int SCM_RESULT;
SCM_RESULT = gtk_bindings_activate(object, keyval, modifiers);
SCM_RETURN(SCM_MAKE_BOOL(SCM_RESULT));
}
  }
}
