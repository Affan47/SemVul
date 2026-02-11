output_to_pane(const char *str)
{
   int w, h, new_y;
   long ivalue;
   GtkWidget *pane_hbox;
   GtkRequisition size_requisition;


   get_pref(PREF_OUTPUT_HEIGHT, &ivalue, NULL);

   if (ivalue < 50) {

      pane_hbox = gtk_paned_get_child2(GTK_PANED(output_pane));
      gtk_widget_size_request(pane_hbox, &size_requisition);
      ivalue = size_requisition.height + 1;
      set_pref(PREF_OUTPUT_HEIGHT, ivalue, NULL, TRUE);
   }
   gdk_window_get_size(window->window, &w, &h);
   new_y = h - ivalue;
   gtk_paned_set_position(GTK_PANED(output_pane), new_y);


   GtkTextIter end_iter;
   GtkTextMark *end_mark;
   gboolean scroll_to_end = FALSE;
   gdouble sbar_value, sbar_page_size, sbar_upper;


   sbar_value = g_output_text->vadjustment->value;
   sbar_page_size = g_output_text->vadjustment->page_size;
   sbar_upper = g_output_text->vadjustment->upper;


   if ((abs((sbar_value+sbar_page_size) - sbar_upper) < sbar_page_size)
       || sbar_page_size == 1) {
      scroll_to_end = TRUE;
   }

   gtk_text_buffer_get_end_iter(g_output_text_buffer, &end_iter);

   if (! g_utf8_validate(str, -1, NULL)) {
      gchar *utf8_text;

      utf8_text = g_locale_to_utf8 (str, -1, NULL, NULL, NULL);
      gtk_text_buffer_insert(g_output_text_buffer, &end_iter, utf8_text, -1);
      g_free(utf8_text);
   } else
      gtk_text_buffer_insert(g_output_text_buffer, &end_iter, str, -1);

   if (scroll_to_end) {
      end_mark = gtk_text_buffer_create_mark(g_output_text_buffer, NULL, &end_iter, TRUE);
      gtk_text_buffer_move_mark(g_output_text_buffer, end_mark, &end_iter);
      gtk_text_view_scroll_to_mark(g_output_text, end_mark, 0, TRUE, 0.0, 0.0);
      gtk_text_buffer_delete_mark(g_output_text_buffer, end_mark);
   }
}
