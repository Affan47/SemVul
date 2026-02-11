pf_normal_map_iterate_until(struct pf_normal_map *pfnm,
                                               struct tile *ptile)
{
  struct pf_map *pfm = PF_MAP(pfnm);
  struct pf_normal_node *node = pfnm->lattice + tile_index(ptile);

  if (NULL == pf_map_parameter(pfm)->get_costs) {

    if (NS_UNINIT == node->status) {

      pf_normal_node_init(pfnm, node, ptile);
    }


    if (!CAN_ENTER_NODE(node)) {
      return FALSE;
    }
  }

  while (NS_PROCESSED != node->status) {
    if (!pf_map_iterate(pfm)) {


      return FALSE;
    }
  }

  return TRUE;
}
