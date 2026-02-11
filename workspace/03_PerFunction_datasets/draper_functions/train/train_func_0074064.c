gtkbox_gtk_box_set_child_packing(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj box_scm;
  GtkBox* box;
  ScmObj child_scm;
  GtkWidget* child;
  ScmObj expand_scm;
  int expand;
  ScmObj fill_scm;
  int fill;
  ScmObj padding_scm;
  u_int padding;
  ScmObj pack_type_scm;
  int pack_type;
  ScmObj SCM_SUBRARGS[6];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-box-set-child-packing");
  for (SCM_i=0; SCM_i<6; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  box_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_BOX_P(box_scm)) Scm_Error("<gtk-box> required, but got %S", box_scm);
  box = SCM_GTK_BOX(box_scm);
  child_scm = SCM_SUBRARGS[1];
  if (!SCM_GTK_WIDGET_P(child_scm)) Scm_Error("<gtk-widget> required, but got %S", child_scm);
  child = SCM_GTK_WIDGET(child_scm);
  expand_scm = SCM_SUBRARGS[2];
  if (!SCM_BOOLP(expand_scm)) Scm_Error("boolean required, but got %S", expand_scm);
  expand = SCM_BOOL_VALUE(expand_scm);
  fill_scm = SCM_SUBRARGS[3];
  if (!SCM_BOOLP(fill_scm)) Scm_Error("boolean required, but got %S", fill_scm);
  fill = SCM_BOOL_VALUE(fill_scm);
  padding_scm = SCM_SUBRARGS[4];
  if (!SCM_UINTEGERP(padding_scm)) Scm_Error("C integer required, but got %S", padding_scm);
  padding = Scm_GetIntegerU(padding_scm);
  pack_type_scm = SCM_SUBRARGS[5];
  if (!SCM_INTEGERP(pack_type_scm)) Scm_Error("C integer required, but got %S", pack_type_scm);
  pack_type = Scm_GetInteger(pack_type_scm);
  {
gtk_box_set_child_packing(box, child, expand, fill, padding, pack_type);
SCM_RETURN(SCM_UNDEFINED);
  }
}
