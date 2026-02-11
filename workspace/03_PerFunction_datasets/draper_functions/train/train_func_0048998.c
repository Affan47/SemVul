p1d_event_handlers_toggle (splotd * sp, gboolean state)
{
  displayd *display;

  if (sp) {
    display = (displayd *) sp->displayptr;

    if (state == on) {
      if (GGOBI_IS_WINDOW_DISPLAY (display)
          && GGOBI_WINDOW_DISPLAY (display)->useWindow)
        sp->key_press_id =
          g_signal_connect (G_OBJECT (GGOBI_WINDOW_DISPLAY (display)->window),
                            "key_press_event", G_CALLBACK (key_press_cb),
                            (gpointer) sp);
    }
    else {
      disconnect_key_press_signal (sp);
    }
  }
}
