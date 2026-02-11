voteinfo_queue_free(void)
{
  if (voteinfo_queue == NULL) {
    return;
  }

  voteinfo_list_iterate(voteinfo_queue, vi) {
    if (vi != NULL) {
      free(vi);
    }
  } voteinfo_list_iterate_end;

  voteinfo_list_destroy(voteinfo_queue);
  voteinfo_queue = NULL;
  voteinfo_queue_current_index = 0;
}
