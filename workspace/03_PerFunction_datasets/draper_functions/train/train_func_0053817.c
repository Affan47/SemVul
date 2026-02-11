gd_tagged_entry_tag_ensure_close_pixbuf (GdTaggedEntryTag *tag,
                                         GtkStyleContext *context)
{
  GtkIconInfo *info;
  gint icon_size;

  if (tag->close_pixbuf != NULL)
    return;

  gtk_icon_size_lookup (GTK_ICON_SIZE_MENU,
                        &icon_size, NULL);

  info = gtk_icon_theme_lookup_icon (gtk_icon_theme_get_default (),
                                     "window-close-symbolic",
                                     icon_size,
                                     GTK_ICON_LOOKUP_GENERIC_FALLBACK);

  tag->close_pixbuf =
    gtk_icon_info_load_symbolic_for_context (info, context,
                                             NULL, NULL);


}
