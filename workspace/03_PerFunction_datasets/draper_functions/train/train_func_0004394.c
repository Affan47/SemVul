history_get (offset)
     int offset;
{
  int local_index = offset - history_base;

  if (local_index >= history_length ||
      local_index < 0 ||
      !the_history)
    return ((HIST_ENTRY *)NULL);
  return (the_history[local_index]);
}
