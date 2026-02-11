create_linkby_notebook (GtkWidget * box, ggobid * gg)
{
  GtkWidget *notebook;

  GSList *l;
  GGobiData *d;

  GtkSelectionMode mode = GTK_SELECTION_SINGLE;
  vartyped vtype = categorical;
  datatyped dtype = all_datatypes;


  notebook = gtk_notebook_new ();
  gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);

  gtk_notebook_set_show_tabs (GTK_NOTEBOOK (notebook), false);
  gtk_box_pack_start (GTK_BOX (box), notebook, true, true, 2);
  g_object_set_data (G_OBJECT (notebook), "SELECTION", (gpointer) mode);
  g_object_set_data (G_OBJECT (notebook), "vartype", (gpointer) vtype);
  g_object_set_data (G_OBJECT (notebook), "datatype", (gpointer) dtype);

  for (l = gg->d; l; l = l->next) {
    d = (GGobiData *) l->data;
    if (g_slist_length (d->vartable)) {
      linkby_notebook_subwindow_add (d, notebook, gg);
    }
  }


  g_signal_connect (G_OBJECT (gg),
                    "variable_added",
                    G_CALLBACK (linkby_notebook_varadded_cb),
                    GTK_OBJECT (notebook));
  g_signal_connect (G_OBJECT (gg),
                    "variable_list_changed",
                    G_CALLBACK (linkby_notebook_varchanged_cb),
                    GTK_OBJECT (notebook));


  g_signal_connect (G_OBJECT (gg),
                    "datad_added",
                    G_CALLBACK (linkby_notebook_adddata_cb),
                    GTK_OBJECT (notebook));

  return notebook;
}
