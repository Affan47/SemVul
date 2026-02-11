gamgi_mesa_rotate_gamgi_list (double angle, double *axis)
{
gamgi_window *window;

for (window = gamgi->window_start; window != NULL; window = window->next)
  {
  if (window->axes == FALSE)
    gamgi_mesa_rotate_window_in (window, angle, axis);
  else
    gamgi_mesa_rotate_window_out (window, angle, axis);
  }
}
