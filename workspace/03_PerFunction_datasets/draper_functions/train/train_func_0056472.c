control_event_newconsensus(const networkstatus_t *consensus)
{
  if (!control_event_is_interesting(EVENT_NEWCONSENSUS))
    return 0;
  return control_event_networkstatus_changed_helper(
           consensus->routerstatus_list, EVENT_NEWCONSENSUS, "NEWCONSENSUS");
}
