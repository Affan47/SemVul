register_cond_class(const char *name, uint name_length,
                                 int flags)
{

  uint32 index;
  PFS_cond_class *entry;

  REGISTER_CLASS_BODY_PART(index, cond_class_array, cond_class_max,
                           name, name_length)

  index= PFS_atomic::add_u32(&cond_class_dirty_count, 1);

  if (index < cond_class_max)
  {
    entry= &cond_class_array[index];
    init_instr_class(entry, name, name_length, flags);
    entry->m_wait_stat.m_control_flag=
      &flag_events_waits_summary_by_event_name;
    entry->m_wait_stat.m_parent= NULL;
    reset_single_stat_link(&entry->m_wait_stat);
    entry->m_index= index;
    PFS_atomic::add_u32(&cond_class_allocated_count, 1);
    return (index + 1);
  }

  cond_class_lost++;
  return 0;
}
