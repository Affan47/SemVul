mx_path_bar_allocate (ClutterActor           *actor,
                      const ClutterActorBox  *box,
                      ClutterAllocationFlags  flags)
{
  GList *c;
  gint n_crumbs;
  MxPadding padding;
  gboolean allocate_pref;
  ClutterActorBox child_box;
  gfloat min_width, nat_width, extra_space;

  MxPathBarPrivate *priv = MX_PATH_BAR (actor)->priv;

  CLUTTER_ACTOR_CLASS (mx_path_bar_parent_class)->allocate (actor, box, flags);

  mx_widget_get_padding (MX_WIDGET (actor), &padding);
  child_box.x1 = padding.left;
  child_box.y1 = padding.top;
  child_box.y2 = box->y2 - box->y1 - padding.bottom;


  clutter_actor_get_preferred_width (actor,
                                     box->y2 - box->y1,
                                     &min_width,
                                     &nat_width);


  if ((box->x2 - box->x1) < nat_width)
    {
      extra_space = box->x2 - box->x1 - min_width;
      if (extra_space < 0)
        extra_space = 0;
      allocate_pref = FALSE;
    }
  else
    {
      extra_space = 0;
      allocate_pref = TRUE;
    }


  n_crumbs = g_list_length (priv->crumbs);
  for (c = priv->crumbs; c; c = c->next)
    {
      gfloat cmin_width, cnat_width;
      ClutterActor *crumb = c->data;

      clutter_actor_get_preferred_width (crumb,
                                         child_box.y2 - child_box.y1,
                                         &cmin_width,
                                         &cnat_width);

      if (!allocate_pref)
        {


          child_box.x2 = child_box.x1 +
            MIN (cmin_width + extra_space / n_crumbs, cnat_width);

          n_crumbs --;
          if (extra_space >= (child_box.x2 - child_box.x1 - cmin_width))
            extra_space -= (child_box.x2 - child_box.x1 - cmin_width);
          else
            extra_space = 0;
        }
      else
        child_box.x2 = child_box.x1 + cnat_width;


      if (!priv->entry && !c->next &&
          (box->x2 - box->x1 - padding.right) > (child_box.x2 - child_box.x1))
        child_box.x2 = box->x2 - box->x1 - padding.right;

      clutter_actor_allocate (crumb, &child_box, flags);
      child_box.x1 = child_box.x2 - MIN (priv->overlap,
                                         (child_box.x2 - child_box.x1));
    }


  if (priv->editable)
    {
      child_box.x2 = box->x2 - box->x1 - padding.right;
      clutter_actor_allocate (priv->entry, &child_box, flags);
    }
}
