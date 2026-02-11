process_recv_line(World *world, int start, int end, gboolean incomplete)
{
  guchar      *converted;
  gsize        output_len;
  guchar      *stripped = NULL;
  GError      *error = NULL;
  gboolean     gag_output = FALSE;
  gboolean     gag_log    = FALSE;
  gint         dummy;
  GtkTextIter  line_start;
  GtkTextIter  line_end;


  if (!incomplete && world->printed_until) {
    gtk_text_buffer_get_iter_at_mark(world->gui->txtBuffer,
                                     &line_start,
                                     world->gui->txtmark_linestart);
    gtk_text_buffer_get_iter_at_mark(world->gui->txtBuffer,
                                     &line_end,
                                     world->gui->txtmark_end);
    gtk_text_buffer_delete(world->gui->txtBuffer,
                           &line_start, &line_end);


    world->gui->ta.ansifsm_state  = ANSIFSM_DATA;
    world->gui->ta.ansiseq_pos = 0;


    world->gui->ta.state = world->gui->ta.saved_state;
  }

  converted = (guchar *) g_convert((gchar *) (world->pbuffer + start),
                                   end - start,
                                   VTE_ENC, world->charset,
                                   NULL, &output_len,
                                   &error);
  if (converted) {
    if (!incomplete) {
      stripped = strip_ansi(converted, output_len);

      match_triggers(world,
                     &stripped, &converted, &output_len,
                     &gag_output, &gag_log,
                     &dummy, NULL);


    } else {
      ansitextview_append_ansi_string(world->gui,
                                      (gchar *) converted, output_len);
    }

    if (!gag_output) {

      if (!world->has_focus) {
        if (!world->has_unread_text) {
          world->has_unread_text = TRUE;
          gtk_label_set_markup(world->gui->lblNotebook, world->new_text_name);
          if (worlds_with_new_text != -1) {
            ++worlds_with_new_text;

            if (!window_has_focus) {
              adjust_window_title();
            }
          }
        }
      }
      if (!incomplete) {
        execute_hook(world, "OnReceivedText", (gchar *) converted);
      }
    }
    g_free(converted);
  } else {
    fprintf(stderr, "Error in charset conversion: %s\n", error->message);
  }

  g_timer_start(world->last_data_written);
}
