gamgi_expat_export_config_window (gamgi_window *window, FILE *fp,
int depth_parent, int *depth_last, gamgi_bool *output, gamgi_bool *error)
{
gamgi_window_class *window_class = gamgi->window;
char string[GAMGI_ENGINE_STRING];
int column;


if (fabs (window_class->rotate_max - GAMGI_GTK_ROTATE_MAX) > GAMGI_MATH_TOLERANCE)
  {
  sprintf (string, "rotate_max=\"%.*f\"",
  gamgi->gamgi->angle, window_class->rotate_max);
  gamgi_expat_export_element (fp, "<window", string,
  depth_parent, depth_last, &column, output, error);
  }

if (fabs (window_class->rotate_step - GAMGI_GTK_ROTATE_STEP) > GAMGI_MATH_TOLERANCE)
  {
  sprintf (string, "rotate_step=\"%.*f\"",
  gamgi->gamgi->angle, window_class->rotate_step);
  gamgi_expat_export_element (fp, "<window", string,
  depth_parent, depth_last, &column, output, error);
  }


if (fabs (window_class->move_max - GAMGI_GTK_MOVE_MAX) > GAMGI_MATH_TOLERANCE)
  {
  sprintf (string, "move_max=\"%.*f\"",
  gamgi->gamgi->angle, window_class->move_max);
  gamgi_expat_export_element (fp, "<window", string,
  depth_parent, depth_last, &column, output, error);
  }

if (fabs (window_class->move_step - GAMGI_GTK_MOVE_STEP) > GAMGI_MATH_TOLERANCE)
  {
  sprintf (string, "move_step=\"%.*f\"",
  gamgi->gamgi->angle, window_class->move_step);
  gamgi_expat_export_element (fp, "<window", string,
  depth_parent, depth_last, &column, output, error);
  }


if (fabs (window_class->scale_max - GAMGI_GTK_SCALE_MAX) > GAMGI_MATH_TOLERANCE)
  {
  sprintf (string, "scale_max=\"%.*f\"",
  gamgi->gamgi->angle, window_class->scale_max);
  gamgi_expat_export_element (fp, "<window", string,
  depth_parent, depth_last, &column, output, error);
  }

if (fabs (window_class->scale_step - GAMGI_GTK_SCALE_STEP) > GAMGI_MATH_TOLERANCE)
  {
  sprintf (string, "scale_step=\"%.*f\"",
  gamgi->gamgi->angle, window_class->scale_step);
  gamgi_expat_export_element (fp, "<window", string,
  depth_parent, depth_last, &column, output, error);
  }

}
