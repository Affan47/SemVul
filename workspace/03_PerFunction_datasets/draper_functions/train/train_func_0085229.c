rl_reset_line_state ()
{
  rl_on_new_line ();

  rl_display_prompt = rl_prompt ? rl_prompt : "";
  forced_display = 1;
  return 0;
}
