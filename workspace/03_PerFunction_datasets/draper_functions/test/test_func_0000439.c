ensure_color(struct rgbcolor *rgb)
{
  fc_assert_ret_val(rgb != NULL, NULL);

  if (!rgb->color) {
    rgb->color = color_alloc(rgb->r, rgb->g, rgb->b);
  }
  return rgb->color;
}
