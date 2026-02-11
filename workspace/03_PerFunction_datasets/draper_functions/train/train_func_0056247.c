cmd_exchangedown (int interactive UNUSED, struct cmdarg **args UNUSED)
{
  rp_frame *frame;

  if ((frame = find_frame_down (current_frame())))
    exchange_with_frame (current_frame(), frame);

  return cmdret_new (RET_SUCCESS, NULL);
}
