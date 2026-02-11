evd_web_dir_set_root (EvdWebDir *self, const gchar *root)
{
  gchar *_root;

  g_return_if_fail (EVD_IS_WEB_DIR (self));
  g_return_if_fail (root != NULL);

  if (self->priv->root != NULL)
    g_free (self->priv->root);

  if (! g_path_is_absolute (root))
    {
      gchar *current_dir;

      current_dir = g_get_current_dir ();
      _root = g_strdup_printf ("%s/%s", current_dir, root);
      g_free (current_dir);
    }
  else
    {
      _root = g_strdup (root);
    }

  self->priv->root = _root;
}
