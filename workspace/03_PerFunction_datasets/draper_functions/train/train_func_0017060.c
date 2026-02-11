create_city_info_table(struct city_dialog *pdialog,
    					 GtkWidget **info_ebox,
					 GtkWidget **info_label)
{
  int i;
  GtkWidget *hbox, *table, *label, *ebox;

  static const char *output_label[NUM_INFO_FIELDS] = { N_("Food:"),
    N_("Prod:"),
    N_("Trade:"),
    N_("Gold:"),
    N_("Luxury:"),
    N_("Science:"),
    N_("Granary:"),
    N_("Change in:"),
    N_("Corruption:"),
    N_("Waste:"),
    N_("Pollution:"),
    N_("Plague Risk:")
  };
  static bool output_label_done;

  hbox = gtk_hbox_new(TRUE, 0);

  table = gtk_table_new(NUM_INFO_FIELDS, 2, FALSE);
  gtk_table_set_row_spacing(GTK_TABLE(table), 2, 10);
  gtk_table_set_row_spacing(GTK_TABLE(table), 5, 10);
  gtk_table_set_row_spacing(GTK_TABLE(table), 7, 10);
  gtk_table_set_col_spacing(GTK_TABLE(table), 0, 5);
  gtk_box_pack_start(GTK_BOX(hbox), table, FALSE, FALSE, 4);

  intl_slist(ARRAY_SIZE(output_label), output_label, &output_label_done);

  for (i = 0; i < NUM_INFO_FIELDS; i++) {
    label = gtk_label_new(output_label[i]);
    gtk_widget_set_name(label, "city_label");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);
    gtk_table_attach(GTK_TABLE(table), label, 0, 1, i, i + 1, GTK_FILL, 0,
		     0, 0);

    ebox = gtk_event_box_new();
    g_object_set_data(G_OBJECT(ebox), "pdialog", pdialog);
    g_signal_connect(ebox, "button_press_event",
	G_CALLBACK(show_info_popup), GUINT_TO_POINTER(i));
    info_ebox[i] = ebox;

    label = gtk_label_new("");
    info_label[i] = label;
    gtk_widget_set_name(label, "city_label");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);

    gtk_container_add(GTK_CONTAINER(ebox), label);

    gtk_table_attach(GTK_TABLE(table), ebox, 1, 2, i, i + 1, GTK_FILL, 0,
		     0, 0);
  }

  gtk_widget_show_all(hbox);
  return hbox;
}
