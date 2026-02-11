fluid_midi_router_handle_begin (fluid_synth_t* synth, int ac, char** av, fluid_ostream_t out)
{
	fluid_midi_router_t* router = synth->midi_router;

	if (ac != 1) {
		fluid_ostream_printf (out, "router_begin requires [note|cc|prog|pbend|cpress|kpress]\n");
		return FLUID_FAILED;
	}

	CHECK_VALID_ROUTER (router, out);

	if (FLUID_STRCMP (av[0], "note") == 0)
		router->cmd_rule_type = FLUID_MIDI_ROUTER_RULE_NOTE;
	else if (FLUID_STRCMP (av[0], "cc") == 0)
		router->cmd_rule_type = FLUID_MIDI_ROUTER_RULE_CC;
	else if (FLUID_STRCMP (av[0], "prog") == 0)
		router->cmd_rule_type = FLUID_MIDI_ROUTER_RULE_PROG_CHANGE;
	else if (FLUID_STRCMP (av[0], "pbend") == 0)
		router->cmd_rule_type = FLUID_MIDI_ROUTER_RULE_PITCH_BEND;
	else if (FLUID_STRCMP (av[0], "cpress") == 0)
		router->cmd_rule_type = FLUID_MIDI_ROUTER_RULE_CHANNEL_PRESSURE;
	else if (FLUID_STRCMP (av[0], "kpress") == 0)
		router->cmd_rule_type = FLUID_MIDI_ROUTER_RULE_KEY_PRESSURE;
	else {
		fluid_ostream_printf (out, "router_begin requires [note|cc|prog|pbend|cpress|kpress]\n");
		return FLUID_FAILED;
	}

	if (router->cmd_rule)
		delete_fluid_midi_router_rule (router->cmd_rule);

	router->cmd_rule = new_fluid_midi_router_rule ();

	if (!router->cmd_rule)
		return FLUID_FAILED;

	return FLUID_OK;
}
