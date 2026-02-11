gtkbindings_gtk_binding_set_by_class(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj type_scm;
  ScmClass* type;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-binding-set-by-class");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  type_scm = SCM_SUBRARGS[0];
  if (!SCM_CLASSP(type_scm)) Scm_Error("class required, but got %S", type_scm);
  type = SCM_CLASS(type_scm);
  {
GType gtype = Scm_ClassToGtkType(type); gpointer gclass;
  GtkBindingSet *bset;
  if (gtype == G_TYPE_INVALID) {
    Scm_Error("given class doesn't correspond to an GObject class: %S", type);
  }
  gclass = g_type_class_ref(gtype);
  bset = gtk_binding_set_by_class(gclass);
  g_type_class_unref(gclass);
  SCM_RETURN(Scm_MakeGtkBindingSet(bset));
  }
}
