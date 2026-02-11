st_theme_node_paint_equal (StThemeNode *node,
                           StThemeNode *other)
{
  StBorderImage *border_image, *other_border_image;
  StShadow *shadow, *other_shadow;
  int i;


  if (node == NULL || other == NULL)
    return FALSE;

  if (node == other)
    return TRUE;

  _st_theme_node_ensure_background (node);
  _st_theme_node_ensure_background (other);

  if (!clutter_color_equal (&node->background_color, &other->background_color))
    return FALSE;

  if (node->background_gradient_type != other->background_gradient_type)
    return FALSE;

  if (node->background_gradient_type != ST_GRADIENT_NONE &&
      !clutter_color_equal (&node->background_gradient_end, &other->background_gradient_end))
    return FALSE;

  if (g_strcmp0 (node->background_image, other->background_image) != 0)
    return FALSE;

  _st_theme_node_ensure_geometry (node);
  _st_theme_node_ensure_geometry (other);

  for (i = 0; i < 4; i++)
    {
      if (node->border_width[i] != other->border_width[i])
        return FALSE;

      if (node->border_width[i] > 0 &&
          !clutter_color_equal (&node->border_color[i], &other->border_color[i]))
        return FALSE;

      if (node->border_radius[i] != other->border_radius[i])
        return FALSE;
    }

  if (node->outline_width != other->outline_width)
    return FALSE;

  if (node->outline_width > 0 &&
      !clutter_color_equal (&node->outline_color, &other->outline_color))
    return FALSE;

  border_image = st_theme_node_get_border_image (node);
  other_border_image = st_theme_node_get_border_image (other);

  if ((border_image == NULL) != (other_border_image == NULL))
    return FALSE;

  if (border_image != NULL && !st_border_image_equal (border_image, other_border_image))
    return FALSE;

  shadow = st_theme_node_get_box_shadow (node);
  other_shadow = st_theme_node_get_box_shadow (other);

  if ((shadow == NULL) != (other_shadow == NULL))
    return FALSE;

  if (shadow != NULL && !st_shadow_equal (shadow, other_shadow))
    return FALSE;

  shadow = st_theme_node_get_background_image_shadow (node);
  other_shadow = st_theme_node_get_background_image_shadow (other);

  if ((shadow == NULL) != (other_shadow == NULL))
    return FALSE;

  if (shadow != NULL && !st_shadow_equal (shadow, other_shadow))
    return FALSE;

  return TRUE;
}
