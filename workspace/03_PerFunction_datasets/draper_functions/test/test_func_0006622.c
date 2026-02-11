xmlrc_parse_apps(xmlDocPtr doc, xmlNodePtr cur)
{
  app_list_t *apps;
  app_t      *app;
  apps = app_list_new();
  cur = cur->xmlChildrenNode;
  while (cur)
  {
    if (xmlStrcmp(cur->name, (const xmlChar *) "app"))
      ERR("cur->name:%s unknown", cur->name);
    app = xmlrc_parse_app(doc, cur);
    if (app != NULL)
      app_list_add(apps, app);
    cur = cur->next;
  }
  return apps;
}
