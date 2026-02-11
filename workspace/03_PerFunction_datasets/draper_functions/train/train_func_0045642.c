_rl_update_final ()
{
  int full_lines;

  full_lines = 0;


  if (_rl_vis_botlin && _rl_last_c_pos == 0 &&
	visible_line[vis_lbreaks[_rl_vis_botlin]] == 0)
    {
      _rl_vis_botlin--;
      full_lines = 1;
    }
  _rl_move_vert (_rl_vis_botlin);

  if (full_lines && _rl_term_autowrap && (VIS_LLEN(_rl_vis_botlin) == _rl_screenwidth))
    {
      char *last_line;

      last_line = &visible_line[vis_lbreaks[_rl_vis_botlin]];
      _rl_move_cursor_relative (_rl_screenwidth - 1, last_line);
      _rl_clear_to_eol (0);
      putc (last_line[_rl_screenwidth - 1], rl_outstream);
    }
  _rl_vis_botlin = 0;
  rl_crlf ();
  fflush (rl_outstream);
  rl_display_fixed++;
}
