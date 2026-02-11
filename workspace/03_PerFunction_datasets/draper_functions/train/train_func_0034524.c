server_option_bitwise_set(struct option *poption, unsigned val)
{
  struct server_option *psoption = SERVER_OPTION(poption);
  char name[MAX_LEN_MSG];

  if (val == psoption->bitwise.value) {
    return FALSE;
  }

  server_option_bitwise_support_base(psoption->bitwise.support_names, val,
                                     name, sizeof(name));
  send_chat_printf("/set %s \"%s\"", psoption->name, name);
  return TRUE;
}
