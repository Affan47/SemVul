mx_box_layout_style_changed (MxWidget *widget,
                             gpointer  userdata)
{
  MxBoxLayout *layout = MX_BOX_LAYOUT (widget);
  MxBoxLayoutPrivate *priv = layout->priv;
  guint spacing;

  mx_stylable_get (MX_STYLABLE (widget),
                   "x-mx-spacing", &spacing,
                   NULL);

  if (!priv->ignore_css_spacing && (priv->spacing != spacing))
    {
      priv->spacing = spacing;
      clutter_actor_queue_relayout (CLUTTER_ACTOR (widget));
    }

  clutter_actor_queue_redraw (CLUTTER_ACTOR (widget));
}
