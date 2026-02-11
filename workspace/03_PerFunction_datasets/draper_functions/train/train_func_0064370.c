set_loop_on (int quiet, int progressive)
{
    state->flags |= STATE_LOOPING;
    if (quiet) {
	state->flags |= STATE_LOOP_QUIET;
    }
    if (progressive) {
	state->flags |= STATE_LOOP_PROG;
    }
}
