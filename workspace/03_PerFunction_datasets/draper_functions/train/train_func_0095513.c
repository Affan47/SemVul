gtkaccellabel_gtk_accel_label_set_accel_closure(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj accel_label_scm;
  GtkAccelLabel* accel_label;
  ScmObj accel_closure_scm;
  ScmProcedure* accel_closure;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-accel-label-set-accel-closure");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  accel_label_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_ACCEL_LABEL_P(accel_label_scm)) Scm_Error("<gtk-accel-label> required, but got %S", accel_label_scm);
  accel_label = SCM_GTK_ACCEL_LABEL(accel_label_scm);
  accel_closure_scm = SCM_SUBRARGS[1];
  if (!SCM_PROCEDUREP(accel_closure_scm)) Scm_Error("procedure required, but got %S", accel_closure_scm);
  accel_closure = SCM_PROCEDURE(accel_closure_scm);
  {
gtk_accel_label_set_accel_closure(accel_label, Scm_MakeGClosure(accel_closure)); SCM_RETURN(SCM_UNDEFINED);
  }
}
