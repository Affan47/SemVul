mx_icon_style_changed_cb (MxWidget *widget)
{
  MxIcon *self = MX_ICON (widget);
  MxIconPrivate *priv = self->priv;

  MxBorderImage *content_image = NULL;
  gboolean changed = FALSE;
  gchar *icon_name = NULL;
  gchar *icon_suffix = NULL;
  gint icon_size = -1;

  mx_stylable_get (MX_STYLABLE (widget),
                   "x-mx-content-image", &content_image,
                   "x-mx-icon-name", &icon_name,
                   "x-mx-icon-size", &icon_size,
                   "x-mx-icon-suffix", &icon_suffix,
                   NULL);


  if (content_image)
    {
      GError *error = NULL;

      priv->is_content_image = TRUE;
      g_signal_handlers_disconnect_by_func (mx_icon_theme_get_default (),
                                            mx_icon_notify_theme_name_cb,
                                            self);

      if (priv->icon_texture)
        {
          clutter_actor_destroy (priv->icon_texture);
          priv->icon_texture = NULL;
        }

      if (content_image->uri)
        priv->icon_texture = clutter_texture_new_from_file (content_image->uri,
                                                            &error);
      if (priv->icon_texture)
        clutter_actor_set_parent (priv->icon_texture, CLUTTER_ACTOR (widget));

      if (error)
        {
          g_warning ("Could not load content image: %s", error->message);
          g_error_free (error);
        }

      g_boxed_free (MX_TYPE_BORDER_IMAGE, content_image);
      g_free (icon_name);

      return;
    }

  if (icon_name && !priv->icon_set &&
      (!priv->icon_name || !g_str_equal (icon_name, priv->icon_name)))
    {
      g_free (priv->icon_name);
      priv->icon_name = g_strdup (icon_name);
      changed = TRUE;

      g_object_notify (G_OBJECT (self), "icon-name");
    }
  else if (!icon_name && !priv->icon_set && priv->icon_name)
    {

      g_free (priv->icon_name);
      priv->icon_name = NULL;
      priv->icon_set = FALSE;

      changed = TRUE;

      g_object_notify (G_OBJECT (self), "icon-name");
    }

  if ((icon_size > 0) && !priv->size_set && (priv->icon_size != icon_size))
    {
      priv->icon_size = icon_size;
      changed = TRUE;

      g_object_notify (G_OBJECT (self), "icon-size");
    }

  if ((icon_suffix != priv->icon_suffix) &&
      (!icon_suffix || !priv->icon_suffix ||
       !g_str_equal (icon_suffix, priv->icon_suffix)))
    {
      g_free (priv->icon_suffix);
      priv->icon_suffix = icon_suffix;

      changed = TRUE;
    }
  else
    g_free (icon_suffix);

  if (changed)
    mx_icon_update (self);
}
