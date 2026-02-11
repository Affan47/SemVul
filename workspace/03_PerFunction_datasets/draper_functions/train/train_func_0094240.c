create_image_type_combo()
{
  GtkWidget *C=gtk_combo_box_new_text();
  GSList *F=writable_formats;
  while(F) {
    gpointer data=F->data;
    GdkPixbufFormat *f=data;
    gtk_combo_box_append_text(GTK_COMBO_BOX(C),gdk_pixbuf_format_get_name (f));
    F=g_slist_next(F);
  }
  gtk_combo_box_append_text(GTK_COMBO_BOX(C),"ppm");
  gtk_widget_set_name (C,"file_type_combo");
  g_signal_connect ((gpointer) C,"changed",on_image_type_changed,NULL);
  return C;
}
