fluid_midi_router_add_rule (fluid_midi_router_t *router, fluid_midi_router_rule_t *rule,
                            int type)
{
	fluid_midi_router_rule_t *free_rules, *next_rule;

	fluid_return_val_if_fail (router != NULL, FLUID_FAILED);
	fluid_return_val_if_fail (rule != NULL, FLUID_FAILED);
	fluid_return_val_if_fail (type >= 0 && type < FLUID_MIDI_ROUTER_RULE_COUNT, FLUID_FAILED);


	fluid_mutex_lock (router->rules_mutex);


	free_rules = router->free_rules;
	router->free_rules = NULL;

	rule->next = router->rules[type];
	router->rules[type] = rule;

	fluid_mutex_unlock (router->rules_mutex);


	for (; free_rules; free_rules = next_rule) {
		next_rule = free_rules->next;
		FLUID_FREE (free_rules);
	}

	return FLUID_OK;
}
