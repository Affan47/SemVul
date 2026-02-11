thread_state_info(THD *tmp)
{
#ifndef EMBEDDED_LIBRARY
  if (tmp->net.reading_or_writing)
  {
    if (tmp->net.reading_or_writing == 2)
      return "Writing to net";
    else if (tmp->command == COM_SLEEP)
      return "";
    else
      return "Reading from net";
  }
  else
#endif
  {
    if (tmp->proc_info)
      return tmp->proc_info;
    else if (tmp->mysys_var && tmp->mysys_var->current_cond)
      return "Waiting on cond";
    else
      return NULL;
  }
}
