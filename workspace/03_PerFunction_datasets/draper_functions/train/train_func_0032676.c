st_button_set_label (StButton    *button,
                     const gchar *text)
{
  StButtonPrivate *priv;
  ClutterActor *label;

  g_return_if_fail (ST_IS_BUTTON (button));

  priv = button->priv;

  g_free (priv->text);

  if (text)
    priv->text = g_strdup (text);
  else
    priv->text = g_strdup ("");

  label = st_bin_get_child (ST_BIN (button));

  if (label && CLUTTER_IS_TEXT (label))
    {
      clutter_text_set_text (CLUTTER_TEXT (label), priv->text);
    }
  else
    {
      label = g_object_new (CLUTTER_TYPE_TEXT,
                            "text", priv->text,
                            "line-alignment", PANGO_ALIGN_CENTER,
                            "ellipsize", PANGO_ELLIPSIZE_END,
                            "use-markup", TRUE,
                            NULL);
      st_bin_set_child (ST_BIN (button), label);
    }


  st_widget_style_changed (ST_WIDGET (button));

  g_object_notify (G_OBJECT (button), "label");
}
