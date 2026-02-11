create_huff_tree (void)


{
   unsigned	i;
   huff_node_t *huff_root = fiasco_calloc (1, sizeof (huff_node_t));


   for (i = 0; i < 33; i++)
      huff_root->index_set [i] = i;
   huff_root->index_set [i] = -1;

   create_huff_node (huff_root, 0);

   return huff_root;
}
