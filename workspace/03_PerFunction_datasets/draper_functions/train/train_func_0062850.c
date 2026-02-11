x_color_lookup (int color)
{
  if (color < 0 || color >= MAX_COLORS ||
      !display_colors[color].enabled) {
    fprintf(stderr, _("Tried to get an invalid color: %d\n"), color);
    return &display_colors[DEFAULT_COLOR];
  } else {
    return &display_colors[color];
  }
}
