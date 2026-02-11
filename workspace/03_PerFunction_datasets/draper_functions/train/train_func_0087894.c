msgqueue_destroy(struct event_msgqueue *msgq)
{
   for( ; msgqueue_length(msgq) > 0; ) {
      sleep( 1 );
   }

   event_del(&msgq->queue_ev);
   circqueue_destroy(msgq->queue);
   sp_close(msgq->push_fd);
   sp_close(msgq->pop_fd);
   free(msgq);
}
