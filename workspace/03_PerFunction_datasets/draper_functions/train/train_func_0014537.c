onRenderingChanged(GObject *obj _U_, VisuRendering *meth,
			       gpointer data _U_)
{
  GtkTreeIter iter;
  gboolean valid;
  VisuRendering* method;
  int i;

  if (meth)
    {
      DBG_fprintf(stderr, "Panel Method: changing rendering method to '%s'.\n",
		  visu_rendering_getName(meth, FALSE));
      i = 0;

      valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(listStoreRenderingMethods), &iter);
      while (valid)
	{
	  gtk_tree_model_get(GTK_TREE_MODEL(listStoreRenderingMethods), &iter,
			     COLUMN_POINTER_TO_DATA, &method,
			     -1);
	  if (method == meth)
	    {
	      gtk_combo_box_set_active(GTK_COMBO_BOX(comboMethod), i);
	      DBG_fprintf(stderr, "Panel Method: ok, new method found at position %d.\n", i);
	      return;
	    }
	  valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(listStoreRenderingMethods), &iter);
	  i += 1;
	}
      g_warning("Can't find the current rendering method ('%s')"
	      " is the combobox of the config panel.",
		visu_rendering_getName(meth, FALSE));
    }
  else
    g_warning("Unsupported NULL rendering method.");
}
