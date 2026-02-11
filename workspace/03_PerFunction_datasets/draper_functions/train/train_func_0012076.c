visu_ui_stipple_combobox_add(VisuUiStippleCombobox *stippleComboBox, guint16 stipple)
{
  GtkTreeIter iter;
  gboolean validIter;
  GObjectClass *klass;
  GtkListStore *model;
  guint tmpStipple;

  g_return_if_fail(VISU_UI_IS_STIPPLE_COMBOBOX(stippleComboBox));


  klass = G_OBJECT_GET_CLASS(stippleComboBox);
  model = GTK_LIST_STORE(VISU_UI_STIPPLE_COMBOBOX_CLASS(klass)->listStoredStipples);
  validIter = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(model), &iter);
  while (validIter)
    {
      gtk_tree_model_get(GTK_TREE_MODEL(model), &iter,
			 COLUMN_STIPPLE_VALUE, &tmpStipple,
			 -1);
      if ((guint16)(tmpStipple) == stipple)
	return ;
      validIter = gtk_tree_model_iter_next(GTK_TREE_MODEL(model), &iter);
    }
  addStippleToModel(&iter, VISU_UI_STIPPLE_COMBOBOX_CLASS(klass), stipple);
}
