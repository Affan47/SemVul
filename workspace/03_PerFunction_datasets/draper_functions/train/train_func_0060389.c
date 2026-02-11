free_rx(RESTORE_CTX *rx)
{
   free_bsr(rx->bsr);
   rx->bsr = NULL;
   free_and_null_pool_memory(rx->JobIds);
   free_and_null_pool_memory(rx->BaseJobIds);
   free_and_null_pool_memory(rx->fname);
   free_and_null_pool_memory(rx->path);
   free_and_null_pool_memory(rx->query);
   free_name_list(&rx->name_list);
}
