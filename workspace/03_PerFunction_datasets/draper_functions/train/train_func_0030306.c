chain_index (int idx, tree chain)
{
  for (; chain && idx > 0; --idx)
    chain = TREE_CHAIN (chain);
  return chain;
}
