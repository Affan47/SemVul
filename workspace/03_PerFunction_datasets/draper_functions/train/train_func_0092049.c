nodelist_add_routerinfo(routerinfo_t *ri)
{
  node_t *node;
  init_nodelist();
  node = node_get_or_create(ri->cache_info.identity_digest);
  node->ri = ri;

  if (node->country == -1)
    node_set_country(node);

  if (authdir_mode(get_options())) {
    const char *discard=NULL;
    uint32_t status = dirserv_router_get_status(ri, &discard);
    dirserv_set_node_flags_from_authoritative_status(node, status);
  }

  return node;
}
