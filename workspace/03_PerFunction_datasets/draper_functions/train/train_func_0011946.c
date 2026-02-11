fluid_midi_router_clear_rules (fluid_midi_router_t *router)
{
	fluid_midi_router_rule_t *del_rules[FLUID_MIDI_ROUTER_RULE_COUNT];
	fluid_midi_router_rule_t *rule, *next_rule, *prev_rule;
	int i;

	fluid_return_val_if_fail (router != NULL, FLUID_FAILED);

	fluid_mutex_lock (router->rules_mutex);

	for (i = 0; i < FLUID_MIDI_ROUTER_RULE_COUNT; i++) {
		del_rules[i] = NULL;
		prev_rule = NULL;


		for (rule = router->rules[i]; rule; rule = next_rule) {
			next_rule = rule->next;

			if (rule->pending_events == 0) {

				if (prev_rule) prev_rule->next = next_rule;
				else if (rule == router->rules[i]) router->rules[i] = next_rule;


				rule->next = del_rules[i];
				del_rules[i] = rule;
			} else {
				rule->waiting = TRUE;
				prev_rule = rule;
			}
		}
	}

	fluid_mutex_unlock (router->rules_mutex);


	for (i = 0; i < FLUID_MIDI_ROUTER_RULE_COUNT; i++) {
		for (rule = del_rules[i]; rule; rule = next_rule) {
			next_rule = rule->next;
			FLUID_FREE (rule);
		}
	}

	return FLUID_OK;
}
