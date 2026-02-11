statusfont_set_cb(GtkFontButton *font_btn, gpointer data)
{
  PangoFontDescription *fontDesc;
  World                *world  = (World *) data;
  WorldGUI             *gui    = world->gui;

  free(world->statusfont);
  world->statusfont = g_strdup(gtk_font_button_get_font_name(font_btn));

  if (gui) {
    GtkWidget *widget = GTK_WIDGET(world->gui->lblStatus);

    fontDesc = pango_font_description_from_string(world->statusfont);
    gtk_widget_modify_font(widget, fontDesc);
    pango_font_description_free(fontDesc);
  }
}
