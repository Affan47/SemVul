set_gretl_echo (int e)
{
    if (check_for_state()) return;

    if (e) {
	state->flags |= STATE_ECHO_ON;
    } else {
	state->flags &= ~STATE_ECHO_ON;
    }
}
