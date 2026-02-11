ladish_cqueue_clear(struct ladish_cqueue * queue_ptr)
{
  struct list_head * node_ptr;
  struct ladish_command * cmd_ptr;

  while (!list_empty(&queue_ptr->queue))
  {
    node_ptr = queue_ptr->queue.next;
    list_del(node_ptr);

    cmd_ptr = list_entry(node_ptr, struct ladish_command, siblings);

    if (cmd_ptr->destructor != NULL)
    {
      cmd_ptr->destructor(cmd_ptr->context);
    }

    free(cmd_ptr);
  }

  queue_ptr->cancel = false;
}
