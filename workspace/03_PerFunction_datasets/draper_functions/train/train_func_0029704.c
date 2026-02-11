host_service_find(struct host_pak *host, const gchar *name)
{
gint flags;
gchar *text, *reply;
struct service_pak *service;

g_assert(host != NULL);
g_assert(name != NULL);


if (g_strrstr(name, "mpi") || g_strrstr(name, "qsub"))
  flags = SERVICE_SECONDARY;
else
  flags = SERVICE_BACKGROUND;


text = g_strdup_printf("which %s\n", name);
reply = host_talk(host, text);
g_free(text);

if (g_strrstr(reply, "not found"))
  {
  g_free(reply);
  reply = NULL;
  }


service = g_malloc(sizeof(struct service_pak));
service->host = host;
service->flags = flags;
service->fullpath = reply;

g_hash_table_insert(host->services, g_strdup(name), service);
}
