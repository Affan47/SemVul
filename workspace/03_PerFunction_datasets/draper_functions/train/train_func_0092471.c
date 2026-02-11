routerset_get_all_nodes(smartlist_t *out, const routerset_t *routerset,
                        const routerset_t *excludeset, int running_only)
{
  tor_assert(out);
  if (!routerset || !routerset->list)
    return;

  if (routerset_is_list(routerset)) {


    SMARTLIST_FOREACH(routerset->list, const char *, name, {
        const node_t *node = node_get_by_nickname(name, 1);
        if (node) {
          if (!running_only || node->is_running)
            if (!routerset_contains_node(excludeset, node))
              smartlist_add(out, (void*)node);
        }
    });
  } else {


    smartlist_t *nodes = nodelist_get_list();
    SMARTLIST_FOREACH(nodes, const node_t *, node, {
        if (running_only && !node->is_running)
          continue;
        if (routerset_contains_node(routerset, node) &&
            !routerset_contains_node(excludeset, node))
          smartlist_add(out, (void*)node);
    });
  }
}
