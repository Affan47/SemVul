get_slotwise_sos_threshold(const lListElem *qinstance)
{
   u_long32  slots_sum = 0;
   lList     *so_list = NULL;
   lListElem *so = NULL;

   if (qinstance != NULL) {
      so_list = lGetList(qinstance, QU_subordinate_list);
      if (so_list != NULL) {
         so = lFirst(so_list);
         if (so != NULL) {
            slots_sum = lGetUlong(so, SO_slots_sum);
         }
      }
   }
   return slots_sum;
}
