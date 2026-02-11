timer_free(timer_entry_t *timer,int take_lock)
{
   if (take_lock) TIMER_LOCK();


   hash_table_remove(timer_id_hash,&timer->id);

   if (take_lock) TIMER_UNLOCK();


   free(timer);
}
