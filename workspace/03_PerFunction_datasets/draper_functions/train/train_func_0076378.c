mx_widget_paint_background (MxWidget *self)
{
  MxWidgetPrivate *priv;
  MxWidgetClass *klass;

  g_return_if_fail (MX_IS_WIDGET (self));

  priv = self->priv;

  klass = MX_WIDGET_GET_CLASS (self);
  klass->paint_background (MX_WIDGET (self),
                          priv->border_image,
                          priv->bg_color);

}
