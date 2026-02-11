GWEN_PluginDescription_new(GWEN_XMLNODE *node){
  GWEN_PLUGIN_DESCRIPTION *pd;
  const char *p;

  GWEN_NEW_OBJECT(GWEN_PLUGIN_DESCRIPTION, pd);
  pd->refCount=1;
  DBG_MEM_INC("GWEN_PLUGIN_DESCRIPTION", 0);
  GWEN_LIST_INIT(GWEN_PLUGIN_DESCRIPTION, pd);
  p=GWEN_XMLNode_GetProperty(node, "name", 0);
  if (!p) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Unnamed plugin");
    GWEN_PluginDescription_free(pd);
    return 0;
  }
  pd->name=strdup(p);
  pd->xmlNode=GWEN_XMLNode_dup(node);

  p=GWEN_XMLNode_GetProperty(node, "i18n", NULL);
  if (!p) {
    DBG_NOTICE(GWEN_LOGDOMAIN, "Plugin has no I18N domain, using GWEN");
    p="gwenhywfar";
  }
  pd->langDomain=strdup(p);

  p=GWEN_XMLNode_GetProperty(node, "type", 0);
  if (!p) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Plugin has no type");
    GWEN_PluginDescription_free(pd);
    return 0;
  }
  pd->type=strdup(p);

  p=GWEN_XMLNode_GetCharValue(node, "version", 0);
  if (p)
    pd->version=strdup(p);
  p=GWEN_XMLNode_GetCharValue(node, "author", 0);
  if (p)
    pd->author=strdup(p);
  p=GWEN_XMLNode_GetCharValue(node, "short", 0);
  if (p)
    pd->shortDescr=strdup(p);
  p=GWEN_XMLNode_GetCharValue(node, "descr", 0);
  if (p)
    pd->longDescr=strdup(p);
  return pd;
}
