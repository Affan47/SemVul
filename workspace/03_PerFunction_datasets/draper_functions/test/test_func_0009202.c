create_month_boxes_texts(GtkWidget *month_vbox)
{
   int i, j, n;
   GtkWidget *hbox_row;
   GtkWidget *vbox;
   GtkWidget *text;
   GtkWidget *event_box;
   char str[80];

   n=0;
   for (i=0; i<6; i++) {
      hbox_row = gtk_hbox_new(TRUE, 0);
      gtk_box_pack_start(GTK_BOX(month_vbox), hbox_row, TRUE, TRUE, 0);
      for (j=0; j<7; j++) {
         vbox = gtk_vbox_new(FALSE, 0);
         gtk_box_pack_start(GTK_BOX(hbox_row), vbox, TRUE, TRUE, 2);
         n=i*7+j;
         if (n<37) {
            sprintf(str, "%d", n + 1);

            month_day_label[n] = gtk_label_new(str);
            gtk_misc_set_alignment(GTK_MISC(month_day_label[n]), 0.0, 0.5);
            gtk_box_pack_start(GTK_BOX(vbox), month_day_label[n], FALSE, FALSE, 0);


            text = month_day[n] = gtk_text_view_new();
            month_day_buffer[n] =
              G_OBJECT(gtk_text_view_get_buffer(GTK_TEXT_VIEW(text)));
            gtk_widget_set_usize(GTK_WIDGET(text), 10, 10);
            gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text), FALSE);
            gtk_text_view_set_editable(GTK_TEXT_VIEW(text), FALSE);
            gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text), GTK_WRAP_WORD);


            event_box = gtk_event_box_new();
            gtk_container_add(GTK_CONTAINER(event_box), text);

            gtk_signal_connect(GTK_OBJECT(event_box), "enter_notify_event",
                               GTK_SIGNAL_FUNC(cb_enter_notify), GINT_TO_POINTER(n));
            gtk_signal_connect(GTK_OBJECT(text), "button_release_event",
                               GTK_SIGNAL_FUNC(cb_enter_selected_day),
                               GINT_TO_POINTER(n));

            gtk_box_pack_start(GTK_BOX(vbox), event_box, TRUE, TRUE, 0);

         }
      }
   }
   glob_last_hbox_row = hbox_row;

   text = gtk_text_view_new();
   all_appts_buffer = G_OBJECT(gtk_text_view_get_buffer(GTK_TEXT_VIEW(text)));
   gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text), FALSE);
   gtk_text_view_set_editable(GTK_TEXT_VIEW(text), FALSE);
   gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text), GTK_WRAP_WORD);
   gtk_widget_set_usize(GTK_WIDGET(text), 10, 10);
   gtk_box_pack_start(GTK_BOX(month_vbox), text, TRUE, TRUE, 4);
}
