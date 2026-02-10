Terminate(gn_data *data, struct gn_statemachine *state)
{
	if (AT_DRVINST(state)) {
		if (AT_DRVINST(state)->cached_capabilities) {
			map_free(&(AT_DRVINST(state)->cached_capabilities));
			AT_DRVINST(state)->cached_capabilities = NULL;
		}
		if (AT_DRVINST(state)->timezone) {
			free(AT_DRVINST(state)->timezone);
			AT_DRVINST(state)->timezone = NULL;
		}
		free(AT_DRVINST(state));
		AT_DRVINST(state) = NULL;
	}
	return pgen_terminate(data, state);
}
