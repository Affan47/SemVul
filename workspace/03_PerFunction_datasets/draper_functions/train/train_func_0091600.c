isrv_want_wr(isrv_state_t *state, int fd)
{
	if (!FD_ISSET(fd, &state->wr)) {
		WR_COUNT++;
		FD_SET(fd, &state->wr);
	}
}
