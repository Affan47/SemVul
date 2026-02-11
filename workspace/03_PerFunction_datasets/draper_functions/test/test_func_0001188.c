execute_call(const struct call *call)
{
  switch (call->type) {
  case OCT_NEW_TURN:
    call->agent->agent.turn_start_notify();
    break;
  case OCT_UNIT:
    call->agent->agent.unit_callbacks[call->cb_type] (call->arg);
    break;
  case OCT_CITY:
    call->agent->agent.city_callbacks[call->cb_type] (call->arg);
    break;
  case OCT_TILE:
    call->agent->agent.tile_callbacks[call->cb_type]
      (index_to_tile(call->arg));
    break;
  }
}
