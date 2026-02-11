clutter_bin_layout_allocate (ClutterLayoutManager   *manager,
                             ClutterContainer       *container,
                             const ClutterActorBox  *allocation,
                             ClutterAllocationFlags  flags)
{
  gfloat allocation_x, allocation_y;
  gfloat available_w, available_h;
  ClutterActor *actor, *child;
  ClutterActorIter iter;

  clutter_actor_box_get_origin (allocation, &allocation_x, &allocation_y);
  clutter_actor_box_get_size (allocation, &available_w, &available_h);

  actor = CLUTTER_ACTOR (container);

  clutter_actor_iter_init (&iter, actor);
  while (clutter_actor_iter_next (&iter, &child))
    {
      ClutterLayoutMeta *meta;
      ClutterBinLayer *layer;
      ClutterActorBox child_alloc = { 0, };
      gdouble x_align, y_align;
      gboolean x_fill, y_fill, is_fixed_position_set;
      float fixed_x, fixed_y;

      if (!CLUTTER_ACTOR_IS_VISIBLE (child))
        continue;

      meta = clutter_layout_manager_get_child_meta (manager,
                                                    container,
                                                    child);
      layer = CLUTTER_BIN_LAYER (meta);

      fixed_x = fixed_y = 0.f;
      g_object_get (child,
                    "fixed-position-set", &is_fixed_position_set,
                    "fixed-x", &fixed_x,
                    "fixed-y", &fixed_y,
                    NULL);


      if (is_fixed_position_set ||
          layer->x_align == CLUTTER_BIN_ALIGNMENT_FIXED)
	{
          if (is_fixed_position_set)
            child_alloc.x1 = fixed_x;
          else
            child_alloc.x1 = clutter_actor_get_x (child);
	}
      else
        child_alloc.x1 = allocation_x;

      if (is_fixed_position_set ||
          layer->y_align == CLUTTER_BIN_ALIGNMENT_FIXED)
	{
	  if (is_fixed_position_set)
            child_alloc.y1 = fixed_y;
          else
	    child_alloc.y1 = clutter_actor_get_y (child);
	}
      else
        child_alloc.y1 = allocation_y;

      child_alloc.x2 = allocation_x + available_w;
      child_alloc.y2 = allocation_y + available_h;

      if (clutter_actor_needs_expand (child, CLUTTER_ORIENTATION_HORIZONTAL))
        {
          ClutterActorAlign align;

          align = clutter_actor_get_x_align (child);
          x_fill = align == CLUTTER_ACTOR_ALIGN_FILL;
          x_align = get_actor_align_factor (align);
        }
      else
        {
          ClutterTextDirection text_dir;

          x_fill = (layer->x_align == CLUTTER_BIN_ALIGNMENT_FILL);

          text_dir = clutter_actor_get_text_direction (child);

          if (!is_fixed_position_set)
            x_align = get_bin_alignment_factor (layer->x_align, text_dir);
          else
            x_align = 0.0;
        }

      if (clutter_actor_needs_expand (child, CLUTTER_ORIENTATION_VERTICAL))
        {
          ClutterActorAlign align;

          align = clutter_actor_get_y_align (child);
          y_fill = align == CLUTTER_ACTOR_ALIGN_FILL;
          y_align = get_actor_align_factor (align);
        }
      else
        {
          y_fill = (layer->y_align == CLUTTER_BIN_ALIGNMENT_FILL);

          if (!is_fixed_position_set)
            y_align = get_bin_alignment_factor (layer->y_align,
                                                CLUTTER_TEXT_DIRECTION_LTR);
          else
            y_align = 0.0;
        }

      clutter_actor_allocate_align_fill (child, &child_alloc,
                                         x_align, y_align,
                                         x_fill, y_fill,
                                         flags);
    }
}
