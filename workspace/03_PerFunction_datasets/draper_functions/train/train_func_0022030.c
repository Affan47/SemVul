ladish_studio_jack_conf_container_destroy(
  struct jack_conf_container * container_ptr)
{
  struct list_head * node_ptr;


  if (!container_ptr->children_leafs)
  {
    while (!list_empty(&container_ptr->children))
    {
      node_ptr = container_ptr->children.next;
      list_del(node_ptr);
      ladish_studio_jack_conf_container_destroy(list_entry(node_ptr, struct jack_conf_container, siblings));
    }
  }
  else
  {
    while (!list_empty(&container_ptr->children))
    {
      node_ptr = container_ptr->children.next;
      list_del(node_ptr);
      ladish_studio_jack_conf_parameter_destroy(list_entry(node_ptr, struct jack_conf_parameter, siblings));
    }
  }

  free(container_ptr->name);
  free(container_ptr);
}
