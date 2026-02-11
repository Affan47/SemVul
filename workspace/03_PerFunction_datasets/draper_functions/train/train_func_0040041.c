sge_tq_get_task_count(sge_tq_queue_t *queue) {
   u_long32 count = 0;

   DENTER(TQ_LAYER, "sge_tq_get_task_count");
   if (queue != NULL) {
      count = sge_sl_get_elem_count(queue->list);
   }
   DRETURN(count);
}
