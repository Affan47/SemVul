gtktable_gtk_table_new(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj rows_scm;
  u_int rows;
  ScmObj columns_scm;
  u_int columns;
  ScmObj homogeneous_scm;
  int homogeneous;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-table-new");
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  rows_scm = SCM_SUBRARGS[0];
  if (!SCM_UINTEGERP(rows_scm)) Scm_Error("C integer required, but got %S", rows_scm);
  rows = Scm_GetIntegerU(rows_scm);
  columns_scm = SCM_SUBRARGS[1];
  if (!SCM_UINTEGERP(columns_scm)) Scm_Error("C integer required, but got %S", columns_scm);
  columns = Scm_GetIntegerU(columns_scm);
  homogeneous_scm = SCM_SUBRARGS[2];
  if (!SCM_BOOLP(homogeneous_scm)) Scm_Error("boolean required, but got %S", homogeneous_scm);
  homogeneous = SCM_BOOL_VALUE(homogeneous_scm);
  {
{
GtkWidget* SCM_RESULT;
SCM_RESULT = gtk_table_new(rows, columns, homogeneous);
SCM_RETURN(SCM_MAKE_GTK_WIDGET(SCM_RESULT));
}
  }
}
