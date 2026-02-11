printLabel(GtkCellLayout *layout _U_, GtkCellRenderer *cell,
                       GtkTreeModel *model, GtkTreeIter *iter, gpointer data)
{
  gpointer pt;
  gchar *str;

  gtk_tree_model_get(model, iter, COLUMN_ELEMENT_POINTER_TO, &pt, -1);
  if (!pt)
    g_object_set(G_OBJECT(cell), "text", _("None"), NULL);
  else if (GPOINTER_TO_INT(pt) == 1)
    g_object_set(G_OBJECT(cell), "text", _("All elements"), NULL);
  else
    {
      str = g_strdup_printf(VISU_UI_ELEMENT_COMBOBOX(data)->format, ((VisuElement*)pt)->name);
      g_object_set(G_OBJECT(cell), "text", str, NULL);
      g_free(str);
    }
}
