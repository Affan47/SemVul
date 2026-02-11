proxy_info_copy(proxy_settings *source, proxy_settings *dest)
{
  dest->type     = source->type;
  dest->server   = g_strdup(source->server   ? source->server   : "");
  dest->port     = g_strdup(source->port     ? source->port     : "");
  dest->user     = g_strdup(source->user     ? source->user     : "");
  dest->password = g_strdup(source->password ? source->password : "");
}
