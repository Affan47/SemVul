cpanel_edgeedit_make (ggobid * gg)
{
  modepaneld *panel;
  GtkWidget *vb, *radio1, *radio2, *w;
  GSList *group;

  gboolean adding_edges = true;

  panel = (modepaneld *) g_malloc (sizeof (modepaneld));
  gg->control_panels = g_list_append (gg->control_panels, (gpointer) panel);
  panel->name = g_strdup (GGOBI (getIModeName) (EDGEED));
  panel->w = gtk_vbox_new (false, VBOX_SPACING);
  gtk_container_set_border_width (GTK_CONTAINER (panel->w), 5);


  vb = gtk_vbox_new (false, 1);
  gtk_container_set_border_width (GTK_CONTAINER (vb), 3);
  gtk_box_pack_start (GTK_BOX (panel->w), vb, false, false, 0);

  radio1 = gtk_radio_button_new_with_mnemonic (NULL, "Add _edges");
  gtk_widget_set_name (radio1, "EDGEEDIT:add_edges_radio_button");
  if (adding_edges)
    GTK_TOGGLE_BUTTON (radio1)->active = true;

  gtk_tooltips_set_tip (GTK_TOOLTIPS (gg->tips), radio1,
                        "Add new edges using the mouse. The right or middle button opens a dialog window; the left button adds an edge using defaults.",
                        NULL);
  g_signal_connect (G_OBJECT (radio1), "toggled",
                    G_CALLBACK (add_edges_or_points_cb), gg);
  gtk_box_pack_start (GTK_BOX (vb), radio1, false, false, 0);

  group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radio1));

  radio2 = gtk_radio_button_new_with_mnemonic (group, "Add _points");
  gtk_widget_set_name (radio2, "EDGEEDIT:add_points_radio_button");
  gtk_tooltips_set_tip (GTK_TOOLTIPS (gg->tips), radio2,
                        "Add points using the mouse.  The right or button opens a dialog window; the left button adds a point using defaults.",
                        NULL);
  gtk_box_pack_start (GTK_BOX (vb), radio2, false, false, 0);

  w = gtk_label_new (tip_edges);
  gtk_label_set_line_wrap (GTK_LABEL (w), true);
  gtk_box_pack_start (GTK_BOX (vb), w, false, false, 0);
  gtk_widget_set_name (w, "EDGEEDIT:tip_label");


  gtk_widget_show_all (panel->w);
}
