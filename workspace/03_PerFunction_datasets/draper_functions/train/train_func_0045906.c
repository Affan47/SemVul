st_shadow_equal (StShadow *shadow,
                 StShadow *other)
{
  g_return_val_if_fail (shadow != NULL, FALSE);
  g_return_val_if_fail (other != NULL, FALSE);


  return (clutter_color_equal (&shadow->color, &other->color) &&
          shadow->xoffset == other->xoffset &&
          shadow->yoffset == other->yoffset &&
          shadow->blur == other->blur &&
          shadow->spread == other->spread &&
          shadow->inset == other->inset);
}
