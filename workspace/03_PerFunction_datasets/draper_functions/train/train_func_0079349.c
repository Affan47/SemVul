init_factions()
{
	int i;


	for (i = 0; i < FACTION_NUMBER_OF_FACTIONS; i++) {
		set_faction_state(FACTION_SELF, i, FRIENDLY);
	}
	set_faction_state(FACTION_SELF, FACTION_BOTS, HOSTILE);


	for (i = 0; i < FACTION_NUMBER_OF_FACTIONS; i++) {
		set_faction_state(FACTION_CIVILIAN, i, FRIENDLY);
	}
	set_faction_state(FACTION_CIVILIAN, FACTION_BOTS, HOSTILE);


	for (i = 0; i < FACTION_NUMBER_OF_FACTIONS; i++) {
		set_faction_state(FACTION_CRAZY, i, FRIENDLY);
	}
	set_faction_state(FACTION_CRAZY, FACTION_BOTS, HOSTILE);
	set_faction_state(FACTION_CRAZY, FACTION_SELF, HOSTILE);


	for (i = 0; i < FACTION_NUMBER_OF_FACTIONS; i++) {
		set_faction_state(FACTION_REDGUARD, i, FRIENDLY);
	}
	set_faction_state(FACTION_REDGUARD, FACTION_BOTS, HOSTILE);
	set_faction_state(FACTION_REDGUARD, FACTION_RESISTANCE, HOSTILE);


	for (i = 0; i < FACTION_NUMBER_OF_FACTIONS; i++) {
		set_faction_state(FACTION_RESISTANCE, i, FRIENDLY);
	}
	set_faction_state(FACTION_RESISTANCE, FACTION_BOTS, HOSTILE);
	set_faction_state(FACTION_RESISTANCE, FACTION_REDGUARD, HOSTILE);


	for (i = 0; i < FACTION_NUMBER_OF_FACTIONS; i++) {
		set_faction_state(FACTION_BOTS, i, HOSTILE);
	}


	for (i = 0; i < FACTION_NUMBER_OF_FACTIONS; i++) {
		set_faction_state(FACTION_SINGULARITY, i, HOSTILE);
	}
	set_faction_state(FACTION_SINGULARITY, FACTION_SELF, FRIENDLY);
	set_faction_state(FACTION_SINGULARITY, FACTION_BOTS, FRIENDLY);


	for (i = 0; i < FACTION_NUMBER_OF_FACTIONS; i++) {
		set_faction_state(FACTION_NEUTRAL, i, FRIENDLY);
	}


	for (i = 0; i < FACTION_NUMBER_OF_FACTIONS; i++) {
		set_faction_state(i, i, FRIENDLY);
	}
}
