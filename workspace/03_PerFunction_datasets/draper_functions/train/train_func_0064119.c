serialize_state (struct RcState const	*state,
		 char const		*state_name,
		 GString		*rc_string)
{
	if (FG_SET & state->flags) {
		g_string_append_printf (rc_string, "\tfg[%s] = '%s'\n", state_name, state->fg);
	}

	if (BG_SET & state->flags) {
		g_string_append_printf (rc_string, "\tbg[%s] = '%s'\n", state_name, state->bg);
	}

	if (BASE_SET & state->flags) {
		g_string_append_printf (rc_string, "\tbase[%s] = '%s'\n", state_name, state->base);
	}

	if (TEXT_SET & state->flags) {
		g_string_append_printf (rc_string, "\ttext[%s] = '%s'\n", state_name, state->text);
	}
}
