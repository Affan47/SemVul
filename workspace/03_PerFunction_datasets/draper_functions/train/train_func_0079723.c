namespaceIdxEncode2 ( int nsp, int idx )
{
  xassert(nsp < NUM_NAMESPACES && idx < NUM_IDX);
  return ( nsp << idxbits ) + idx;
}
