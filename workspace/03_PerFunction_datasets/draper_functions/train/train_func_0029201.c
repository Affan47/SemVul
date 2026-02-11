find_capability(const char *capab)
{
  const dlink_node *ptr = NULL;

  DLINK_FOREACH(ptr, cap_list.head)
  {
    const struct Capability *cap = ptr->data;

    if (cap->cap && !irccmp(cap->name, capab))
      return cap->cap;
  }

  return 0;
}
