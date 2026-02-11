gucharmap_search_dialog_start_search (GucharmapSearchDialog *search_dialog,
                                      GucharmapDirection     direction)
{
  GucharmapSearchDialogPrivate *priv = GUCHARMAP_SEARCH_DIALOG_GET_PRIVATE (search_dialog);

  if (priv->search_state != NULL && !_entry_is_empty (GTK_ENTRY (priv->entry)))
    _gucharmap_search_dialog_fire_search (search_dialog, direction);
  else
    gtk_window_present (GTK_WINDOW (search_dialog));
}
