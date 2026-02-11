default_chars_frame_create(charpick_data *curr_data)
{
  GtkWidget *dialog = curr_data->propwindow;
  GtkWidget *dbox, *vbox, *vbox1, *vbox2, *vbox3;
  GtkWidget *hbox;
  GtkWidget *label;
  GtkWidget *scrolled;
  GtkWidget *button;

  dbox = gtk_dialog_get_content_area(GTK_DIALOG (dialog));

  vbox = gtk_vbox_new (FALSE, 18);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
  gtk_box_pack_start (GTK_BOX (dbox), vbox, TRUE, TRUE, 0);

  vbox1 = create_hig_catagory (vbox, _("Character Palette"));

  vbox3 = gtk_vbox_new (FALSE, 6);
  gtk_box_pack_start (GTK_BOX (vbox1), vbox3, TRUE, TRUE, 0);

  label = gtk_label_new_with_mnemonic(_("_Palettes:"));
  gtk_box_pack_start(GTK_BOX(vbox3), label, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
  gtk_widget_show(label);

  hbox = gtk_hbox_new (FALSE, 12);
  gtk_box_pack_start (GTK_BOX (vbox3), hbox, TRUE, TRUE, 0);
  scrolled = create_palettes_tree (curr_data, label);
  gtk_box_pack_start (GTK_BOX (hbox), scrolled, TRUE, TRUE, 0);

  vbox2 = gtk_vbox_new (FALSE, 6);
  gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, FALSE, 0);
  button = gtk_button_new_from_stock (GTK_STOCK_ADD);
  gtk_box_pack_start (GTK_BOX (vbox2), button, FALSE, FALSE, 0);
  g_signal_connect (G_OBJECT (button), "clicked",
  			     G_CALLBACK (add_palette), curr_data);
  set_access_namedesc (button, _("Add button"),
				         _("Click to add a new palette"));

  button = gtk_button_new_from_stock (CHARPICK_STOCK_EDIT);
  gtk_box_pack_start (GTK_BOX (vbox2), button, FALSE, FALSE, 0);
  g_signal_connect (G_OBJECT (button), "clicked",
  			     G_CALLBACK (edit_palette), curr_data);
  g_object_set_data (G_OBJECT (scrolled), "edit_button", button);
  set_access_namedesc (button, _("Edit button"),
				         _("Click to edit the selected palette"));

  button = gtk_button_new_from_stock (GTK_STOCK_DELETE);
  gtk_box_pack_start (GTK_BOX (vbox2), button, FALSE, FALSE, 0);
  g_signal_connect (G_OBJECT (button), "clicked",
  			     G_CALLBACK (delete_palette), curr_data);
  g_object_set_data (G_OBJECT (scrolled), "delete_button", button);
  set_access_namedesc (button, _("Delete button"),
				         _("Click to delete the selected palette"));

  if ( ! key_writable (PANEL_APPLET (curr_data->applet), "chartable"))
	  gtk_widget_set_sensitive (vbox3, FALSE);

  return;
}
