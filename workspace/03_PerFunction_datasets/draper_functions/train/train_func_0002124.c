bg_send_pidfile(void)
{
  bg_comm_t message;

  message.comm_type = BG_COMM_TRANSFERPF;
  message.comm_data.transferpf.len = strlen(pid_file);


  if (write(bg.comm_send, &message, sizeof(message)) < 0)
    goto error;

  if (write(bg.comm_send, pid_file, message.comm_data.transferpf.len) < 0)
    goto error;
  return;
error:
  fatal("COMMUNICATION THROUGH PIPE BROKE.", 0);
}
