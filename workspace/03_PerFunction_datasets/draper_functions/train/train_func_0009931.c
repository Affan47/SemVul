follow_if_link (GucharmapCharmap *charmap,
                GtkTextIter *iter)
{
  GucharmapCharmapPrivate *priv = charmap->priv;
  GSList *tags = NULL, *tagp = NULL;

  tags = gtk_text_iter_get_tags (iter);
  for (tagp = tags;  tagp != NULL;  tagp = tagp->next)
    {
      GtkTextTag *tag = tagp->data;
      gunichar uc;


      uc = GPOINTER_TO_UINT (g_object_get_data (G_OBJECT (tag), "link-character")) - 1;

      if (uc != (gunichar)(-1))
        {
          g_signal_emit (charmap, gucharmap_charmap_signals[LINK_CLICKED], 0,
                         gucharmap_chartable_get_active_character (priv->chartable),
                         uc);
          gucharmap_charmap_set_active_character (charmap, uc);
          break;
        }
    }

  if (tags)
    g_slist_free (tags);
}
