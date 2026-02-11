set_barpadding (struct cmdarg **args)
{
  int x, y;

  if (args[0] == NULL)
    return cmdret_new (RET_SUCCESS, "%d %d", defaults.bar_x_padding, defaults.bar_y_padding);

  x = ARG(0,number);
  y = ARG(1,number);

  if (x >= 0 && y >= 0)
    {
      defaults.bar_x_padding = x;
      defaults.bar_y_padding = y;
    }
  else
    return cmdret_new (RET_FAILURE, "defbarpadding: invalid arguments");

  return cmdret_new (RET_SUCCESS, NULL);
}
