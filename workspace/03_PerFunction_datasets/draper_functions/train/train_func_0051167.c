PrintWarn(const char *str, ...)
{
  va_list args;

  va_start(args, str);
  vsnprintf(message_buf, sizeof(message_buf), str, args);
  va_end(args);

  (* cur_funcs->print_msg)("Warning: %s", message_buf);

  cur_comms->total_big_warn++;

#if DEBUG_ENABLED
  PrintDebug("Warning: %s", message_buf);
#endif
}
