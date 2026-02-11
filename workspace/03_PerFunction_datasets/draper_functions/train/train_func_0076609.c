unlog(ulong cookie, my_xid xid)
{
  PAGE *p=pages+(cookie/tc_log_page_size);
  my_xid *x=(my_xid *)(data+cookie);

  DBUG_ASSERT(*x == xid);
  DBUG_ASSERT(x >= p->start && x < p->end);
  *x=0;

  mysql_mutex_lock(&p->lock);
  p->free++;
  DBUG_ASSERT(p->free <= p->size);
  set_if_smaller(p->ptr, x);
  if (p->free == p->size)
    statistic_decrement(tc_log_cur_pages_used, &LOCK_status);
  if (p->waiters == 0)
    mysql_cond_signal(&COND_pool);
  mysql_mutex_unlock(&p->lock);
  return 0;
}
