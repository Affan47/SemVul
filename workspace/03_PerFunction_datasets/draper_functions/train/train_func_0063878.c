msg_run_add(struct msg *msg)
{
  if (++msg->run_length >= msg->run_num_allocated) {
    if (msg_run_expand_to_hold_more(msg)<0)
      goto error;
  }
  msg->run_data[msg->run_length - 1] = run_new();
  if (msg->run_data[msg->run_length - 1] == NULL)
    goto error;
  msg->run_set = 1;
  return (msg->run_data[msg->run_length - 1]);
error:
  --msg->run_length;
  return (NULL);
}
