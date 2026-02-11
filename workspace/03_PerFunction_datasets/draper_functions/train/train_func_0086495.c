new_tree(int count)
{
   TREE_ROOT *root;
   uint32_t size;

   if (count < 1000) {
      count = 1000;
   }
   root = (TREE_ROOT *)malloc(sizeof(TREE_ROOT));
   memset(root, 0, sizeof(TREE_ROOT));

   size = count * (BALIGN(sizeof(TREE_NODE)) + 40);
   if (count > 1000000 || size > (MAX_BUF_SIZE / 2)) {
      size = MAX_BUF_SIZE;
   }
   Dmsg2(400, "count=%d size=%d\n", count, size);
   malloc_buf(root, size);
   root->cached_path_len = -1;
   root->cached_path = get_pool_memory(PM_FNAME);
   root->type = TN_ROOT;
   root->fname = "";
   return root;
}
