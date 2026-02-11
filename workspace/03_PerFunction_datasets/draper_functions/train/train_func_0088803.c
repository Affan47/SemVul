pf_jumbo_map_iterate(struct pf_map *pfm)
{
  struct pf_normal_map *pfnm = PF_NORMAL_MAP(pfm);
  struct tile *tile = pfm->tile;
  int index = tile_index(tile);
  struct pf_normal_node *node = pfnm->lattice + index;
  const struct pf_parameter *params = pf_map_parameter(pfm);


  adjc_dir_iterate(tile, tile1, dir) {


    int index1 = tile_index(tile1);
    struct pf_normal_node *node1 = pfnm->lattice + index1;
    int priority, cost1, extra_cost1;


    if (node1->status == NS_PROCESSED) {

      continue;
    }

    if (NS_UNINIT == node1->status) {


      cost1 = PF_IMPOSSIBLE_MC;
      extra_cost1 = 0;
    } else {
      cost1 = node1->cost;
      extra_cost1 = node1->extra_cost;
    }


    priority = params->get_costs(tile, dir, tile1, node->cost,
                                 node->extra_cost, &cost1,
                                 &extra_cost1, params);
    if (priority >= 0) {


      node1->cost = cost1;
      node1->extra_cost = extra_cost1;
      node1->status = NS_NEW;
      node1->dir_to_here = dir;
      pq_insert(pfnm->queue, index1, -priority);
    }
  } adjc_dir_iterate_end;


  do {
    if (!pq_remove(pfnm->queue, &index)) {

      return FALSE;
    }

  } while (NS_NEW != pfnm->lattice[index].status);


  pfm->tile = index_to_tile(index);
  pfnm->lattice[index].status = NS_PROCESSED;

  return TRUE;
}
