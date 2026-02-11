thd_timer_destroy(thd_timer_t *ttp)
{
  DBUG_ENTER("thd_timer_destroy");

  my_timer_delete(&ttp->timer);
  pthread_mutex_destroy(&ttp->mutex);
  my_free(ttp);

  DBUG_VOID_RETURN;
}
