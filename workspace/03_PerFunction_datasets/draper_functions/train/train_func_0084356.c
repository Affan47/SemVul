client_disappeared(struct graph * graph_ptr, uint64_t id)
{
  struct list_head * node_ptr;
  struct monitor * monitor_ptr;

  list_for_each(node_ptr, &graph_ptr->monitors)
  {
    monitor_ptr = list_entry(node_ptr, struct monitor, siblings);
    monitor_ptr->client_disappeared(monitor_ptr->context, id);
  }
}
