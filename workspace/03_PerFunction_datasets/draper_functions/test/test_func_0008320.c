m_histogram(GtkWidget *, cchar *menu)
{
   if (menu) zfuncs::F1_help_topic = "brightness_dist";

   if (! Dpxm8) return;

   if (winhisto) {
      histogram_paint();
      return;
   }

   winhisto = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(winhisto),ZTX("Brightness Distribution"));
   gtk_window_set_transient_for(GTK_WINDOW(winhisto),MWIN);
   gtk_window_set_default_size(GTK_WINDOW(winhisto),300,200);
   GtkWidget * vbox = gtk_vbox_new(0,3);
   gtk_container_add(GTK_CONTAINER(winhisto),vbox);

   winhistoH = gtk_drawing_area_new();
   gtk_box_pack_start(GTK_BOX(vbox),winhistoH,1,1,3);

   winhistoB = gtk_drawing_area_new();
   gtk_box_pack_start(GTK_BOX(vbox),winhistoB,0,0,0);
   gtk_widget_set_size_request(winhistoB,300,12);

   G_SIGNAL(winhisto,"destroy",histogram_destroy,0);
   G_SIGNAL(winhistoH,"expose-event",histogram_paint,0);
   G_SIGNAL(winhistoB,"expose-event",histogram_paint,0);

   gtk_widget_show_all(winhisto);

   return;
}
