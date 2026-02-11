set_inputwidth (struct cmdarg **args)
{
  if (args[0] == NULL)
    return cmdret_new (RET_SUCCESS, "%d", defaults.input_window_size);

  if (ARG(0,number) < 0)
    return cmdret_new (RET_FAILURE, "definputwidth: invalid argument");
  else
    defaults.input_window_size = ARG(0,number);

  return cmdret_new (RET_SUCCESS, NULL);
}
