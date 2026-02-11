gtk_spell_checker_attach (GtkSpellChecker *spell, GtkTextView *view)
{
  g_return_val_if_fail (GTK_SPELL_IS_CHECKER (spell), FALSE);
  g_return_val_if_fail (GTK_IS_TEXT_VIEW (view), FALSE);
  g_return_val_if_fail (gtk_text_view_get_buffer (view), FALSE);
  g_return_val_if_fail (spell->priv->view == NULL, FALSE);


  GtkSpellChecker *attached;
  attached = g_object_get_data (G_OBJECT (view), GTK_SPELL_OBJECT_KEY);
  g_return_val_if_fail (attached == NULL, FALSE);


  spell->priv->view = view;
  g_object_ref (view);
  g_object_ref_sink (spell);

  g_object_set_data (G_OBJECT (view), GTK_SPELL_OBJECT_KEY, spell);

  g_signal_connect_swapped (view, "destroy",
                            G_CALLBACK (gtk_spell_checker_detach), spell);
  g_signal_connect (view, "button-press-event",
                    G_CALLBACK (button_press_event), spell);
  g_signal_connect (view, "populate-popup",
                    G_CALLBACK (populate_popup), spell);
  g_signal_connect (view, "popup-menu",
                    G_CALLBACK (popup_menu_event), spell);
  g_signal_connect (view, "notify::buffer",
                    G_CALLBACK (buffer_changed), spell);

  set_buffer (spell, gtk_text_view_get_buffer (view));

  return TRUE;
}
