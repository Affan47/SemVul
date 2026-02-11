gtkmain_gtk_idle_remove_by_data(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj proc_scm;
  ScmObj proc;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-idle-remove-by-data");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  proc_scm = SCM_SUBRARGS[0];
  proc = (proc_scm);
  {
gtk_idle_remove_by_data(proc); SCM_RETURN(SCM_UNDEFINED);
  }
}
