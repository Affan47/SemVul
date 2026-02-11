mx_entry_set_hint_text (MxEntry     *entry,
                        const gchar *text)
{
  MxEntryPrivate *priv;

  g_return_if_fail (MX_IS_ENTRY (entry));

  priv = entry->priv;

  g_free (priv->hint);

  priv->hint = g_strdup (text);

  if (!strcmp (clutter_text_get_text (CLUTTER_TEXT (priv->entry)), "")
      && !HAS_FOCUS (priv->entry))
    {
      priv->hint_visible = TRUE;

      clutter_text_set_text (CLUTTER_TEXT (priv->entry), priv->hint);
      mx_stylable_set_style_pseudo_class (MX_STYLABLE (entry), "indeterminate");
      if (clutter_text_get_password_char (CLUTTER_TEXT (priv->entry)) != 0)
        {
          clutter_text_set_password_char (CLUTTER_TEXT (priv->entry), 0);
        }
    }
}
