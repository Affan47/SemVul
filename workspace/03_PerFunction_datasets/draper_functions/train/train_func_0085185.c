opcode_output_stream(void)
{
  int16_t stream_number =(int16_t) op[0];

  TRACE_LOG("Opcode: OUTPUT_STREAM.\n");

  if (stream_number == 0)
    return;

#ifdef ENABLE_TRACING
  if (((int16_t)op[0]) < 0)
  {
    TRACE_LOG("Closing stream ");
  }
  else
  {
    TRACE_LOG("Opening stream ");
  }
  TRACE_LOG("%d.\n", (((int16_t)op[0]) < 0 ? -((int16_t)op[0]) : op[0]));
#endif

  if ((stream_number < -4) || (stream_number > 4))
    i18n_translate_and_exit(
        libfizmo_module_name,
        i18n_libfizmo_INVALID_OUTPUT_STREAM_NUMBER_P0D,
        -1,
        (long int)stream_number);

  if (stream_number == 1)
    stream_1_active = true;

  else if (stream_number == -1)
    stream_1_active = false;

  else if (stream_number == 2)
    z_mem[0x11] |= 1;

  else if (stream_number == -2)
    z_mem[0x11] &= 0xfe;

  else if (stream_number == 3)
  {
    if (++stream_3_current_depth == MAXIMUM_STREAM_3_DEPTH)
      i18n_translate_and_exit(
          libfizmo_module_name,
          i18n_libfizmo_MAXIMUM_STREAM_3_DEPTH_P0D_EXCEEDED,
          -1,
          MAXIMUM_STREAM_3_DEPTH);

    stream_3_start[stream_3_current_depth] = z_mem + op[1];
    stream_3_index[stream_3_current_depth] = z_mem + op[1] + 2;

    store_word(stream_3_start[stream_3_current_depth], 0);

    TRACE_LOG("stream-3 depth: %d.\n", stream_3_current_depth);

    TRACE_LOG("Current stream-3 dest is %p.\n",
        stream_3_start[stream_3_current_depth]);
  }

  else if (stream_number == -3)
  {
    if (stream_3_current_depth >= 0)
    {
      TRACE_LOG("stream-3 depth: %d.\n", stream_3_current_depth);
      stream_3_current_depth--;
    }
  }

  else if (stream_number == 4)
    stream_4_active = true;

  else if (stream_number == -4)
    stream_4_active = false;
}
