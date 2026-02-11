cause_a_unit_changed_for_agent(const char *name_of_calling_agent,
                                    struct unit *punit)
{
  struct my_agent *agent = agent_by_name(name_of_calling_agent);

  fc_assert_ret(agent->agent.unit_callbacks[CB_CHANGE] != NULL);
  enqueue_call(agent, OCT_UNIT, CB_CHANGE, punit->id);
  call_handle_methods();
}
