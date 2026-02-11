game_restore(state_t **_s, char *game_name)
{
	state_t *s;
	int debug_state = _debugstate_valid;

	sciprintf("Restoring savegame '%s'...\n", game_name);
	s = gamestate_restore(*_s, game_name);

	if (!s) {
		sciprintf("Restoring gamestate '%s' failed.\n", game_name);
		return 1;
	}
	_debugstate_valid = debug_state;
	script_abort_flag = 0;
	s->restarting_flags = 0;

	s->execution_stack_pos = -1;

	_init_stack_base_with_selector(s, s->selector_map.replay);


	send_selector(s, s->game_obj, s->game_obj,
		      s->stack_base, 2,
		      s->stack_base);

	*_s = s = _game_run(s, 1);

	sciprintf(" Game::play() finished.\n");
	return 0;
}
