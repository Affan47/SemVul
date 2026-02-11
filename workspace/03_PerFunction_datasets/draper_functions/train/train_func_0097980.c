gt_blindtrie_resize(GtBlindtrie *blindtrie,unsigned int maxnumofnodes)
{
  gt_assert(maxnumofnodes > 0);
  if (blindtrie->allocatedBlindtrienode > maxnumofnodes)
  {
    blindtrie->allocatedBlindtrienode = maxnumofnodes;
    blindtrie->spaceBlindtrienode
      = gt_realloc(blindtrie->spaceBlindtrienode,
                   sizeof (*blindtrie->spaceBlindtrienode) *
                   blindtrie->allocatedBlindtrienode);
  }
}
