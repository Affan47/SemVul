process_timeouts(ares_channel channel, struct timeval *now)
{
  time_t t;
  struct query *query;
  struct list_node* list_head;
  struct list_node* list_node;


  for (t = channel->last_timeout_processed; t <= now->tv_sec; t++)
    {
      list_head = &(channel->queries_by_timeout[t % ARES_TIMEOUT_TABLE_SIZE]);
      for (list_node = list_head->next; list_node != list_head; )
        {
          query = list_node->data;
          list_node = list_node->next;
          if (query->timeout.tv_sec && ares__timedout(now, &query->timeout))
            {
              query->error_status = ARES_ETIMEOUT;
              ++query->timeouts;
              next_server(channel, query, now);
            }
        }
     }
  channel->last_timeout_processed = now->tv_sec;
}
