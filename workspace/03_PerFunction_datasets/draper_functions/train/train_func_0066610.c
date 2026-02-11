ladish_studio_iterate_rooms(
  void * context,
  bool (* callback)(
    void * context,
    ladish_room_handle room))
{
  struct list_head * node_ptr;
  ladish_room_handle room;

  list_for_each(node_ptr, &g_studio.rooms)
  {
    room = ladish_room_from_list_node(node_ptr);
    if (!callback(context, room))
    {
      return false;
    }
  }

  return true;
}
