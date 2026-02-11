mx_label_single_line_mode_cb (ClutterText *text,
                              GParamSpec  *pspec,
                              MxLabel     *self)
{
  MxLabelPrivate *priv = self->priv;
  if (!clutter_text_get_single_line_mode (text) && priv->fade_out)
    mx_label_set_fade_out (self, FALSE);
}
