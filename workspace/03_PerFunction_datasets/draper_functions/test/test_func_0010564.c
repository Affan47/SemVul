get_nano_slew_error(void)
{
  if (nano_slew_error == 0)
    return 0.0;

  return nano_slew_error / 1e9;
}
