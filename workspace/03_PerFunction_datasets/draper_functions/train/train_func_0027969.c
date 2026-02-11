free_dir_ff_pkt(FF_PKT *dir_ff_pkt)
{
   free(dir_ff_pkt->fname);
   free(dir_ff_pkt->link);
   free_pool_memory(dir_ff_pkt->sys_fname);
   if (dir_ff_pkt->fname_save) {
      free_pool_memory(dir_ff_pkt->fname_save);
   }
   if (dir_ff_pkt->link_save) {
      free_pool_memory(dir_ff_pkt->link_save);
   }
   free(dir_ff_pkt);
}
