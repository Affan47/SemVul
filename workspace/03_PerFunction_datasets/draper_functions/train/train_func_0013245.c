mx_kinetic_scroll_view_get_preferred_height (ClutterActor *actor,
                                             gfloat        for_width,
                                             gfloat       *min_height_p,
                                             gfloat       *nat_height_p)
{
  MxKineticScrollViewPrivate *priv = MX_KINETIC_SCROLL_VIEW (actor)->priv;

  CLUTTER_ACTOR_CLASS (mx_kinetic_scroll_view_parent_class)->
    get_preferred_height (actor, for_width, NULL, nat_height_p);

  if (min_height_p && priv->scroll_policy != MX_SCROLL_POLICY_HORIZONTAL)
    {
      MxPadding padding;

      mx_widget_get_padding (MX_WIDGET (actor), &padding);
      *min_height_p = padding.top + padding.bottom;
    }
}
