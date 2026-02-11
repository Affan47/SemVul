xtensa_reorder_segments (void)
{
  segT sec;
  segT last_sec = 0;
  int old_count = 0;
  int new_count = 0;

  for (sec = stdoutput->sections; sec != NULL; sec = sec->next)
    {
      last_sec = sec;
      old_count++;
    }


  xtensa_reorder_seg_list (literal_head, last_sec);


  for (sec = stdoutput->sections; sec != NULL; sec = sec->next)
    new_count++;
  gas_assert (new_count == old_count);
}
