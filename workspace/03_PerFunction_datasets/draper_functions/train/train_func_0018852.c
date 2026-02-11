fill_background_tiles (ChamplainView *view)
{
  DEBUG_LOG ()

  ChamplainViewPrivate *priv = view->priv;
  ClutterActorIter iter;
  ClutterActor *child;
  gint x_count, y_count, x_first, y_first;
  gint x, y;
  gfloat width, height;
  gboolean have_children = TRUE;

  clutter_content_get_preferred_size (priv->background_content, &width, &height);

  x_count = ceil ((gfloat) priv->viewport_width / width) + 3;
  y_count = ceil ((gfloat) priv->viewport_height / height) + 3;

  x_first = (gint)priv->viewport_x / width - 1;
  y_first = (gint)priv->viewport_y / height - 1;

  clutter_actor_iter_init (&iter, priv->background_layer);

  for (x = x_first; x < x_first + x_count; ++x)
    {
      for (y = y_first; y < y_first + y_count; ++y)
        {
          if (!have_children || !clutter_actor_iter_next (&iter, &child))
            {
              have_children = FALSE;
              child = clutter_actor_new ();
              clutter_actor_set_size (child, width, height);
              clutter_actor_set_content (child, priv->background_content);
              clutter_actor_add_child (priv->background_layer, child);
            }
          champlain_viewport_set_actor_position (CHAMPLAIN_VIEWPORT (priv->viewport),
              child,
              (x * width) - priv->bg_offset_x,
              (y * height) - priv->bg_offset_y);
          child = clutter_actor_get_next_sibling (child);
        }
    }

  if (have_children)
    {
      while (clutter_actor_iter_next (&iter, &child))
          clutter_actor_iter_destroy (&iter);
    }
}
