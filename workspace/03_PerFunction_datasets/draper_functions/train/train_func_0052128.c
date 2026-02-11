gt_clustered_set_union_find_change_cluster_number(GtClusteredSetUF *cs_uf,
                                                  unsigned long first_elem,
                                                  unsigned long target)
{

  unsigned long i;
  i = first_elem;
  while (1)
  {
    cs_uf->cluster_elems[i].cluster_num = target;
    if ((i = cs_uf->cluster_elems[i].next_elem) == cs_uf->num_of_elems)
      break;
  }
}
