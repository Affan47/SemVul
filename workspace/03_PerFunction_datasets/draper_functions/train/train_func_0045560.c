general_log_print(THD *thd, enum enum_server_command command,
                               const char *format, va_list args)
{
  uint message_buff_len= 0;
  char message_buff[MAX_LOG_BUFFER_SIZE];


  if (format)
    message_buff_len= my_vsnprintf(message_buff, sizeof(message_buff),
                                   format, args);
  else
    message_buff[0]= '\0';

  return general_log_write(thd, command, message_buff, message_buff_len);
}
