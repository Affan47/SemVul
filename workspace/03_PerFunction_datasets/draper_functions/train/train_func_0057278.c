clear_pending_onions(void)
{
  while (ol_list) {
    onion_queue_t *victim = ol_list;
    ol_list = victim->next;
    tor_free(victim->onionskin);
    tor_free(victim);
  }
  ol_list = ol_tail = NULL;
  ol_length = 0;
}
