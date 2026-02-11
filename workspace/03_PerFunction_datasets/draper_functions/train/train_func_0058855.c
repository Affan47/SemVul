gtkaccelgroup_gtk_accel_groups_from_object(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj object_scm;
  GObject * object;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-accel-groups-from-object");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  object_scm = SCM_SUBRARGS[0];
  if (!SCM_GOBJECT_P(object_scm)) Scm_Error("<g-object> required, but got %S", object_scm);
  object = SCM_GOBJECT_OBJECT(object_scm);
  {
GSList *lis = gtk_accel_groups_from_object(object);
  ScmObj r = Scm_GoSListToList(lis);

  SCM_RETURN(r);
  }
}
