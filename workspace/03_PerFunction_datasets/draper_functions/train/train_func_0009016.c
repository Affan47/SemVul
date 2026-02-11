HuffmanTree_decode(const HuffmanTree* tree, unsigned* decoded, unsigned* result, unsigned* treepos, unsigned char bit)
{
  if((*treepos) >= tree->numcodes) return 11;

  (*result) = tree->tree2d.data[2 * (*treepos) + bit];
  (*decoded) = ((*result) < tree->numcodes);

  if(*decoded) (*treepos) = 0;
  else (*treepos) = (*result) - tree->numcodes;

  return 0;
}
