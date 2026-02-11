get_we_colors_tab(World *world, GtkBuilder *ui_builder)
{
  GObject  *panel;
  GtkTable *table;
  GObject  *colorBtnAnsi;
  GObject  *colorBtnDeffore;
  GObject  *colorBtnDefbold;
  GObject  *colorBtnDefback;
  GObject  *colorBtnDefboldback;
  gchar     btnname[18];
  int       i;

  panel = gtk_builder_get_object(ui_builder, "we_panel_colors");


  table = GTK_TABLE(gtk_builder_get_object(ui_builder, "table_ansi_colors"));
  gtk_table_set_col_spacing(table, 2, 32);

  for (i = 0; i < 16; ++i) {
    sprintf(btnname, "colorBtnAnsi[%d]", i);
    colorBtnAnsi = gtk_builder_get_object(ui_builder, btnname);
    gtk_color_button_set_color(GTK_COLOR_BUTTON(colorBtnAnsi),
                               &world->ansicolors[i]);
    g_object_set_data(colorBtnAnsi, "colorptr", &world->ansicolors[i]);
  }


  table = GTK_TABLE(gtk_builder_get_object(ui_builder, "table_default_colors"));
  gtk_table_set_col_spacing(table, 2, 32);

  colorBtnDeffore = gtk_builder_get_object(ui_builder, "colorBtnDeffore");
  gtk_color_button_set_color(GTK_COLOR_BUTTON(colorBtnDeffore),
                             world->deffore);
  g_object_set_data(colorBtnDeffore, "colorptr", world->deffore);

  colorBtnDefbold = gtk_builder_get_object(ui_builder, "colorBtnDefbold");
  gtk_color_button_set_color(GTK_COLOR_BUTTON(colorBtnDefbold),
                             world->defbold);
  g_object_set_data(colorBtnDefbold, "colorptr", world->defbold);

  colorBtnDefback = gtk_builder_get_object(ui_builder, "colorBtnDefback");
  gtk_color_button_set_color(GTK_COLOR_BUTTON(colorBtnDefback),
                             world->defback);
  g_object_set_data(colorBtnDefback, "colorptr", world->defback);

  colorBtnDefboldback = gtk_builder_get_object(ui_builder,
                                               "colorBtnDefboldback");
  gtk_color_button_set_color(GTK_COLOR_BUTTON(colorBtnDefboldback),
                             world->defboldback);
  g_object_set_data(colorBtnDefboldback, "colorptr", world->defboldback);

  return panel;
}
