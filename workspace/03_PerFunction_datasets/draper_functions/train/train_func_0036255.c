dimage_color_menu_item_update (GtkWidget *widget, gpointer data)
{
  gimp_menu_item_update (widget, data);
  if (dc_int.do_preview)
    do_preview ();
}
