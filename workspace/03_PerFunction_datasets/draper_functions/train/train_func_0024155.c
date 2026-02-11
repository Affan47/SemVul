clutter_actor_paint_node (ClutterActor     *actor,
                          ClutterPaintNode *root)
{
  ClutterActorPrivate *priv = actor->priv;
  ClutterActorBox box;
  ClutterColor bg_color;

  if (root == NULL)
    return FALSE;

  box.x1 = 0.f;
  box.y1 = 0.f;
  box.x2 = clutter_actor_box_get_width (&priv->allocation);
  box.y2 = clutter_actor_box_get_height (&priv->allocation);

  bg_color = priv->bg_color;

  if (CLUTTER_ACTOR_IS_TOPLEVEL (actor))
    {
      ClutterPaintNode *node;
      CoglFramebuffer *fb;
      CoglBufferBit clear_flags;

      fb = _clutter_stage_get_active_framebuffer (CLUTTER_STAGE (actor));

      if (clutter_stage_get_use_alpha (CLUTTER_STAGE (actor)))
        {
          bg_color.alpha = clutter_actor_get_paint_opacity_internal (actor)
                         * priv->bg_color.alpha
                         / 255;
        }
      else
        bg_color.alpha = 255;

      clear_flags = COGL_BUFFER_BIT_DEPTH;
      if (!clutter_stage_get_no_clear_hint (CLUTTER_STAGE (actor)))
        clear_flags |= COGL_BUFFER_BIT_COLOR;

      node = _clutter_root_node_new (fb, &bg_color, clear_flags);
      clutter_paint_node_set_name (node, "stageClear");
      clutter_paint_node_add_rectangle (node, &box);
      clutter_paint_node_add_child (root, node);
      clutter_paint_node_unref (node);
    }
  else if (priv->bg_color_set &&
           !clutter_color_equal (&priv->bg_color, CLUTTER_COLOR_Transparent))
    {
      ClutterPaintNode *node;

      bg_color.alpha = clutter_actor_get_paint_opacity_internal (actor)
                     * priv->bg_color.alpha
                     / 255;

      node = clutter_color_node_new (&bg_color);
      clutter_paint_node_set_name (node, "backgroundColor");
      clutter_paint_node_add_rectangle (node, &box);
      clutter_paint_node_add_child (root, node);
      clutter_paint_node_unref (node);
    }

  if (priv->content != NULL)
    _clutter_content_paint_content (priv->content, actor, root);

  if (CLUTTER_ACTOR_GET_CLASS (actor)->paint_node != NULL)
    CLUTTER_ACTOR_GET_CLASS (actor)->paint_node (actor, root);

  if (clutter_paint_node_get_n_children (root) == 0)
    return FALSE;

#ifdef CLUTTER_ENABLE_DEBUG
  if (CLUTTER_HAS_DEBUG (PAINT))
    {

      _clutter_paint_node_dump_tree (root);
    }
#endif

  _clutter_paint_node_paint (root);

  return TRUE;
}
