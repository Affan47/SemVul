tree_alloc(TREE_ROOT *root, int size)
{
   char *buf;
   int asize = BALIGN(size);

   if (root->mem->rem < asize) {
      uint32_t mb_size;
      if (root->total_size >= (MAX_BUF_SIZE / 2)) {
         mb_size = MAX_BUF_SIZE;
      } else {
         mb_size = MAX_BUF_SIZE / 2;
      }
      malloc_buf(root, mb_size);
   }
   root->mem->rem -= asize;
   buf = root->mem->mem;
   root->mem->mem += asize;
   return buf;
}
