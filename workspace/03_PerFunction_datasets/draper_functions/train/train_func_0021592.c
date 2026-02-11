escp2_set_dot_size(stp_vars_t *v)
{
  escp2_privdata_t *pd = get_privdata(v);

  if (pd->drop_size >= 0)
    stp_send_command(v, "\033(e", "bcc", 0, pd->drop_size);
}
