set_panel_hccme (const char *s)
{
    if (check_for_state()) return;

    if (!strcmp(s, "Arellano")) {
	state->flags &= ~STATE_USE_PCSE;
    } else if (!strcmp(s, "PCSE")) {
	state->flags |= STATE_USE_PCSE;
    }
}
