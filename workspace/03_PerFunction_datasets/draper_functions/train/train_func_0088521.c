server_option_str_set(struct option *poption, const char *str)
{
  struct server_option *psoption = SERVER_OPTION(poption);

  if (0 == strcmp(psoption->string.value, str)) {
    return FALSE;
  }

  send_chat_printf("/set %s %s", psoption->name, str);
  return TRUE;
}
