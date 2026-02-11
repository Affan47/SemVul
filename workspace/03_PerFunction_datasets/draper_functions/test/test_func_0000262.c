theme_color_system_read(struct section_file *file)
{
  int i;
  struct theme_color_system *colors = fc_malloc(sizeof(*colors));

  fc_assert_ret_val(ARRAY_SIZE(color_names) == COLOR_THEME_LAST, NULL);
  for (i = 0; i < COLOR_THEME_LAST; i++) {
    colors->colors[i].r
      = secfile_lookup_int_default(file, 0, "colors.%s0.r", color_names[i]);
    colors->colors[i].g
      = secfile_lookup_int_default(file, 0, "colors.%s0.g", color_names[i]);
    colors->colors[i].b
      = secfile_lookup_int_default(file, 0, "colors.%s0.b", color_names[i]);
    colors->colors[i].a
      = secfile_lookup_int_default(file, 0, "colors.%s0.a", color_names[i]);
    colors->colors[i].color = NULL;
  }

  return colors;
}
