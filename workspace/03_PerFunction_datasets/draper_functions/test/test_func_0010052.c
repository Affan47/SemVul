get_check_shift (int check_size)
{
  int check_shift = 0;
  g_return_val_if_fail (check_size >= 0, 4);

  while (!(check_size & 1))
    {
      check_shift++;
      check_size >>= 1;
    }

  return check_shift;
}
