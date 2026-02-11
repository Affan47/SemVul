enqueue_call(struct my_agent *agent,
			 enum oct type,
			 enum callback_type cb_type, ...)
{
  va_list ap;
  struct call *pcall2;
  int arg = 0;
  const struct tile *ptile;
  bool added = FALSE;

  va_start(ap, cb_type);

  if (client_is_observer()) {
    return;
  }

  switch (type) {
  case OCT_UNIT:
  case OCT_CITY:
    arg = va_arg(ap, int);
    break;
  case OCT_TILE:
    ptile = va_arg(ap, const struct tile *);
    arg = tile_index(ptile);
    break;
  case OCT_NEW_TURN:

    break;
  }
  va_end(ap);

  pcall2 = fc_malloc(sizeof(struct call));

  pcall2->agent = agent;
  pcall2->type = type;
  pcall2->cb_type = cb_type;
  pcall2->arg = arg;


  call_list_both_iterate(agents.calls, plink, pcall) {
    if (calls_are_equal(pcall, pcall2)) {

      free(pcall2);
      return;
    }
    if (pcall->agent->agent.level - pcall2->agent->agent.level > 0) {


      call_list_insert_before(agents.calls, pcall2, plink);
      added = TRUE;
      break;
    }
  } call_list_both_iterate_end;

  if (!added) {
    call_list_append(agents.calls, pcall2);
  }

  log_todo_lists("A: adding call");


  update_turn_done_button_state();
}
