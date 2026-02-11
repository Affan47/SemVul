barchart_event_handlers_toggle (displayd * display, splotd * sp,
                                gboolean state, ProjectionMode pmode,
                                InteractionMode imode)
{
  if (!GGOBI_IS_WINDOW_DISPLAY (display))
    return;

  if (state == on) {
    GtkObject *winobj = GTK_OBJECT (GGOBI_WINDOW_DISPLAY (display)->window);

    sp->key_press_id =
      g_signal_connect (winobj, "key_press_event",
                        G_CALLBACK (key_press_cb), (gpointer) sp);


    sp->press_id = g_signal_connect (G_OBJECT (sp->da),
                                     "button_press_event",
                                     G_CALLBACK (button_press_cb),
                                     (gpointer) sp);
    sp->release_id = g_signal_connect (G_OBJECT (sp->da),
                                       "button_release_event",
                                       G_CALLBACK (button_release_cb),
                                       (gpointer) sp);
  }
  else {
    disconnect_key_press_signal (sp);
    disconnect_button_press_signal (sp);
    disconnect_button_release_signal (sp);
  }
}
