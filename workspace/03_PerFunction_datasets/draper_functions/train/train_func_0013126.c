RecordStats(HeapStats* stats) {
  *stats->global_handle_count = 0;
  *stats->weak_global_handle_count = 0;
  *stats->pending_global_handle_count = 0;
  *stats->near_death_global_handle_count = 0;
  *stats->free_global_handle_count = 0;
  for (NodeIterator it(this); !it.done(); it.Advance()) {
    *stats->global_handle_count += 1;
    if (it.node()->state() == Node::WEAK) {
      *stats->weak_global_handle_count += 1;
    } else if (it.node()->state() == Node::PENDING) {
      *stats->pending_global_handle_count += 1;
    } else if (it.node()->state() == Node::NEAR_DEATH) {
      *stats->near_death_global_handle_count += 1;
    } else if (it.node()->state() == Node::FREE) {
      *stats->free_global_handle_count += 1;
    }
  }
}
