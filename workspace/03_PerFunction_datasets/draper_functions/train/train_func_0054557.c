huffman_tree_set_codes_rec(GtHuffmanTree *h_tree)
{
  const char leftbit = 0, rightbit = 1;
  if (h_tree != NULL) {
    if (h_tree->leftchild != NULL) {
        h_tree->leftchild->code.code = h_tree->code.code<< 1 | leftbit;
        h_tree->rightchild->code.code = h_tree->code.code<< 1 | rightbit;
        h_tree->leftchild->code.numofbits =
          h_tree->rightchild->code.numofbits = h_tree->code.numofbits + 1;
        huffman_tree_set_codes_rec(h_tree->leftchild);
        huffman_tree_set_codes_rec(h_tree->rightchild);
    }
  }
}
