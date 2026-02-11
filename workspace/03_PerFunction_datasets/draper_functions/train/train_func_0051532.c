room_templates_enum(void * context, bool (* callback)(void * context, ladish_room_handle room))
{
  struct list_head * node_ptr;

  maybe_create_room_templates();

  list_for_each(node_ptr, &g_room_templates)
  {
    if (!callback(context, ladish_room_from_list_node(node_ptr)))
    {
      return false;
    }
  }

  return true;
}
