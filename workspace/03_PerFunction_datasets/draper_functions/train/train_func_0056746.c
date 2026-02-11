move_to_new_line (int old, int new, WINDOW *window)
{
  if (old == -1)
    {
      info_error ("%s", msg_cant_find_point);
    }
  else
    {
      int goal;

      if (new >= window->line_count || new < 0)
        return;

      goal = window_get_goal_column (window);
      window->goal_column = goal;

      window->point = window->line_starts[new] - window->node->contents;
      window->point += window_chars_to_goal (window, goal);
      info_show_point (window);
    }
}
