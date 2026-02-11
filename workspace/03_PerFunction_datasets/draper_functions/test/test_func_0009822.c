visu_ui_stipple_combobox_getStamp(VisuUiStippleCombobox *stippleComboBox, guint16 stipple)
{
  GtkTreeIter iter;
  gboolean validIter;
  GdkPixbuf *pixbuf;
  guint cl;
  GtkListStore *model;

  g_return_val_if_fail(VISU_UI_IS_STIPPLE_COMBOBOX(stippleComboBox) && stipple, (GdkPixbuf*)0);

  model = VISU_UI_STIPPLE_COMBOBOX_CLASS(G_OBJECT_GET_CLASS(stippleComboBox))->listStoredStipples;
  validIter = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(model), &iter);
  while (validIter)
    {
      pixbuf = (GdkPixbuf*)0;
      gtk_tree_model_get(GTK_TREE_MODEL(model), &iter,
			 COLUMN_STIPPLE_PIXBUF, &pixbuf,
			 COLUMN_STIPPLE_VALUE, &cl,
			 -1);
      if (stipple == (guint16)cl)
	return pixbuf;
      validIter = gtk_tree_model_iter_next(GTK_TREE_MODEL(model), &iter);
    }
  return (GdkPixbuf*)0;
}
