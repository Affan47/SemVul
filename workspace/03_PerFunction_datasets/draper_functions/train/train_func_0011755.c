scatmat_var_selected (gint jvar, displayd * display)
{
  gint pos = -1;
  GList *l;
  GtkTableChild *child;
  GtkWidget *da;
  splotd *sp;

  for (l = (GTK_TABLE (display->table))->children; l; l = l->next) {
    child = (GtkTableChild *) l->data;
    da = child->widget;
    sp = (splotd *) g_object_get_data (G_OBJECT (da), "splotd");
    if (sp->p1dvar == jvar) {
      pos = child->left_attach;
      break;
    }
  }

  return pos;
}
