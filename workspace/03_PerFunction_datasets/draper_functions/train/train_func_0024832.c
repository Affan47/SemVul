write_bsr(UAContext *ua, RESTORE_CTX &rx, FILE *fd)
{
   bool first = true;
   uint32_t LastIndex = 0;
   uint32_t total_count = 0;
   char *p;
   JobId_t JobId;
   RBSR *bsr;
   if (*rx.JobIds == 0) {
      for (bsr=rx.bsr; bsr; bsr=bsr->next) {
         total_count += write_bsr_item(bsr, ua, rx, fd, first, LastIndex);
      }
      return total_count;
   }
   for (p=rx.JobIds; get_next_jobid_from_list(&p, &JobId) > 0; ) {
      for (bsr=rx.bsr; bsr; bsr=bsr->next) {
         if (JobId == bsr->JobId) {
            total_count += write_bsr_item(bsr, ua, rx, fd, first, LastIndex);
         }
      }
   }
   return total_count;
}
