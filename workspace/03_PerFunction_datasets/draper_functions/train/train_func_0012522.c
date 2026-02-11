visu_ui_element_combobox_setSelection(VisuUiElementCombobox* wd, const gchar *name)
{
  GtkTreeIter iter;
  gboolean valid;
  gpointer *pt;

  g_return_val_if_fail(VISU_UI_IS_ELEMENT_COMBOBOX(wd) && name, FALSE);

  DBG_fprintf(stderr, "VisuUi ElementCombobox: select a new element '%s'.\n",
              name);

  for (valid = gtk_tree_model_get_iter_first(wd->filter, &iter);
       valid; valid = gtk_tree_model_iter_next(wd->filter, &iter))
    {
      gtk_tree_model_get(wd->filter, &iter, COLUMN_ELEMENT_POINTER_TO, &pt, -1);
      if (pt && GPOINTER_TO_INT(pt) != 1 && !strcmp(((VisuElement*)pt)->name, name))
	{
	  gtk_combo_box_set_active_iter(GTK_COMBO_BOX(wd), &iter);
	  return TRUE;
	}
    }
  return FALSE;
}
