timer_remove(timer_id id)
{
   timer_queue_t *queue = NULL;
   timer_entry_t *timer;

   TIMER_LOCK();


   if (!(timer = timer_find_by_id(id))) {
      TIMER_UNLOCK();
      return(-1);
   }


   if (timer->queue) {
      queue = timer->queue;
      timer_remove_from_queue_atomic(queue,timer);
   }


   timer_free_id(id);


   free(timer);
   TIMER_UNLOCK();


   if (queue)
      pthread_cond_signal(&queue->schedule);
   return(0);
}
