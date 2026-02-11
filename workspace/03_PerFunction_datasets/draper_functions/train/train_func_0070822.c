gt_chain_get_fragnum(const GtChain *chain, unsigned long idx)
{
  gt_assert(chain);
  gt_assert(idx < gt_array_size(chain->fragments));
  return *(unsigned long*) gt_array_get(chain->fragments, idx);
}
