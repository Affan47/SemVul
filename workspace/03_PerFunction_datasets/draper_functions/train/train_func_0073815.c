opcode_set_window(void)
{
  TRACE_LOG("Opcode: SET_WINDOW\n");
  TRACE_LOG("New window number: %d.\n", op[0]);

  if (op[0] == 1) {
    if (
        (upper_window_height == 0)
        &&
        (bool_equal(auto_open_upper_window, true))
       )
    {


      TRACE_LOG("Opening upper window with 1 line for set_window.\n");

#ifndef DISABLE_BLOCKBUFFER
      blockbuf_resize(
          upper_window_buffer,
          (int)active_interface->get_screen_width_in_characters(),
          1);
#endif

      active_interface->split_window((int16_t)1);

      upper_window_height = 1;
    }

#ifndef DISABLE_BLOCKBUFFER
    if (active_window_number != 1) {
      set_blockbuf_cursor(upper_window_buffer, 0, 0);
    }
#endif
  }

  active_window_number = (int16_t)op[0];
  active_interface->set_window((int16_t)op[0]);
}
