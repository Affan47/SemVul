blindtrie_nodestartpos_get(const GtBlindtrie *blindtrie,
                                                GtBlindtriesnodeptr node)
{
  gt_assert(blindtrie_isleaf(blindtrie,node));
  return blindtrie->spaceBlindtrienode[node].either1.nodestartpos;
}
