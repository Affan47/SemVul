rl_on_new_line ()
{
  if (visible_line)
    visible_line[0] = '\0';

  _rl_last_c_pos = _rl_last_v_pos = 0;
  _rl_vis_botlin = last_lmargin = 0;
  if (vis_lbreaks)
    vis_lbreaks[0] = vis_lbreaks[1] = 0;
  visible_wrap_offset = 0;
  return 0;
}
