operator new(size_t size)
{
  CallbackListEntry *ptr = _free_list;

  if (ptr == NULL)
    {
      alloc_entries();
      return ::new CallbackListEntry(0, 0, 0, 0);
    }

  _free_list = ptr->_next;
  ptr->_next = 0;
  return ptr;
}
