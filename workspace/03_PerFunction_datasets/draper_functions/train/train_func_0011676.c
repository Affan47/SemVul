create_and_append_happiness_page(struct city_dialog *pdialog)
{
  GtkWidget *page, *label, *table, *align, *right, *left, *frame;
  const char *tab_title = _("Happ_iness");


  page = gtk_hbox_new(FALSE, 6);
  gtk_container_set_border_width(GTK_CONTAINER(page), 8);
  label = gtk_label_new_with_mnemonic(tab_title);
  gtk_notebook_append_page(GTK_NOTEBOOK(pdialog->notebook), page, label);


  left = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(page), left, FALSE, TRUE, 0);


  frame = gtk_frame_new(_("Info"));
  gtk_box_pack_start(GTK_BOX(left), frame, FALSE, TRUE, 0);

  align = gtk_alignment_new(0.5, 0, 0, 0);
  gtk_container_add(GTK_CONTAINER(frame), align);

  table = create_city_info_table(pdialog,
                                 pdialog->happiness.info_ebox,
                                 pdialog->happiness.info_label);
  gtk_container_add(GTK_CONTAINER(align), table);


  if (game.info.citizen_nationality) {
    pdialog->happiness.citizens = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left), pdialog->happiness.citizens,
                       TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pdialog->happiness.citizens),
                       citizens_dialog_display(pdialog->pcity),
                       TRUE, TRUE, 0);
  }


  right = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(page), right, TRUE, TRUE, 0);


  frame = gtk_frame_new(_("City map"));
  gtk_widget_set_size_request(frame, CITY_MAP_MIN_SIZE_X,
                              CITY_MAP_MIN_SIZE_Y);
  gtk_box_pack_start(GTK_BOX(right), frame, TRUE, TRUE, 0);

  city_dialog_map_create(pdialog, &pdialog->happiness.map_canvas);
  gtk_container_add(GTK_CONTAINER(frame), pdialog->happiness.map_canvas.sw);


  pdialog->happiness.widget = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(right), pdialog->happiness.widget, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(pdialog->happiness.widget),
                     get_top_happiness_display(pdialog->pcity), TRUE, TRUE, 0);


  gtk_widget_show_all(page);
}
