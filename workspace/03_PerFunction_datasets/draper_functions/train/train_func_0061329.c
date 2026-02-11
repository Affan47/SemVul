register_thread_class(const char *name, uint name_length,
                                     int flags)
{

  uint32 index;
  PFS_thread_class *entry;

  for (index= 0; index < thread_class_max; index++)
  {
    entry= &thread_class_array[index];

    if ((entry->m_name_length == name_length) &&
        (strncmp(entry->m_name, name, name_length) == 0))
      return (index + 1);
  }

  index= PFS_atomic::add_u32(&thread_class_dirty_count, 1);

  if (index < thread_class_max)
  {
    entry= &thread_class_array[index];
    DBUG_ASSERT(name_length <= PFS_MAX_INFO_NAME_LENGTH);
    strncpy(entry->m_name, name, name_length);
    entry->m_name_length= name_length;
    entry->m_enabled= true;
    PFS_atomic::add_u32(&thread_class_allocated_count, 1);
    return (index + 1);
  }

  thread_class_lost++;
  return 0;
}
