gth_chain_collection_sort(GthChainCollection *chain_collection)
{
  gt_assert(chain_collection);
  if (gt_array_size(chain_collection->chains)) {
    qsort(gt_array_get_space(chain_collection->chains),
          gt_array_size(chain_collection->chains), sizeof (GthChain*),
          compare_chains);
  }
}
