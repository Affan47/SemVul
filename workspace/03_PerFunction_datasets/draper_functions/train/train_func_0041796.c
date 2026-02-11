parse_player(Config *conf, xmlDocPtr doc, xmlNodePtr node, void *user_data) {
  int id;
  xmlChar *str;
  Config_player *cplay;
  nodeparsers playertags[] = { {"action",parse_player_action} };

  str = xmlGetProp(node, (const xmlChar *)"id");
  if (str == NULL) {
    WARN(_("Player tag without id found"));
    xmlFree(str);
    return FALSE;
  }
  id = atoi((char *)str);
  xmlFree(str);
  str = xmlGetProp(node, (const xmlChar *)"name");
  if (str == NULL) {
    WARN(_("Player tag without name found"));
    xmlFree(str);
    return FALSE;
  }
  cplay = list_search(conf->players, cmp_config_player,&id);
  if (cplay != NULL) {
    list_del(conf->players,cplay);
    del_config_player(cplay);
  }
  cplay = new_config_player(id, (char *)str);
  xmlFree(str);
  list_append(conf->players,cplay);
  id = parse_xmlnodes(conf,doc,node->xmlChildrenNode,playertags,1,cplay);
  return id;
}
