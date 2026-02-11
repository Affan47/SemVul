meta_frames_get_theme_variant (MetaFrames  *frames,
                               const gchar *variant)
{
  GtkStyleContext *style;

  style = g_hash_table_lookup (frames->style_variants, variant);
  if (style == NULL)
    {
      style = meta_theme_create_style_context (gtk_widget_get_screen (GTK_WIDGET (frames)), variant);
      g_hash_table_insert (frames->style_variants, g_strdup (variant), style);
    }

  return style;
}
