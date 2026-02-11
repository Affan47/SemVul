rt_set_powersave_mode (int enable)
{
  unsigned char r;

  if (rt_read_register_immediate (REG_MOVE_CONTROL_TEST, 1, &r) < 0)
    return -1;
  if (r & 0x04)
    {
      if (enable == 1)
	return 0;
      r &= ~0x04;
    }
  else
    {
      if (enable == 0)
	return 0;
      r |= 0x04;
    }
  if (rt_set_one_register (REG_MOVE_CONTROL_TEST, r) < 0 ||
      rt_set_one_register (REG_MOVE_CONTROL_TEST, r) < 0)
    return -1;
  return 0;
}
