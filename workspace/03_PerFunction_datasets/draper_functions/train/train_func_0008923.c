console_setcolorstate (color_state state)
{
  switch (state) {
    case COLOR_STATE_STANDARD:
      console_current_color = console_standard_color;
      break;
    case COLOR_STATE_NORMAL:
      console_current_color = console_normal_color;
      break;
    case COLOR_STATE_HIGHLIGHT:
      console_current_color = console_highlight_color;
      break;
    default:
      console_current_color = console_standard_color;
      break;
  }

  console_color_state = state;
}
