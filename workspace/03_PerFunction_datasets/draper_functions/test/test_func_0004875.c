CheckLabels() {
	int i;
	State *state;
	Action *action;

	for (i=0; i < lastStateNr+1; i++) {
		existLabel[i] = false;
	}

	for (state = firstState->next; state != NULL; state = state->next) {
		for (action = state->firstAction; action != NULL; action = action->next) {
			existLabel[action->target->state->nr] = true;
		}
	}
}
