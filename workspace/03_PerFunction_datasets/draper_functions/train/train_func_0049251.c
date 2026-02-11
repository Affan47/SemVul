gfarm_auth_request_loop_ask_method(int events, int fd, void *closure,
	const struct timeval *t)
{
	struct gfarm_auth_request_state *state = closure;
	gfarm_int32_t method;
	int rv;
	struct timeval timeout;

	method = gfarm_auth_trial_table[state->auth_method_index].method;
	while (method != GFARM_AUTH_METHOD_NONE &&
	    (state->methods & state->server_methods & (1 << method)) == 0) {
		method =
		    gfarm_auth_trial_table[++state->auth_method_index].method;
	}
	state->error = gfp_xdr_send(state->conn, "i", method);
	if (state->error == GFARM_ERR_NO_ERROR &&
	    (state->error = gfp_xdr_flush(state->conn)) == GFARM_ERR_NO_ERROR){
		gfarm_fd_event_set_callback(state->readable,
		    gfarm_auth_request_dispatch_method, state);
		timeout.tv_sec = GFARM_AUTH_TIMEOUT; timeout.tv_usec = 0;
		if ((rv = gfarm_eventqueue_add_event(state->q,
		    state->readable, &timeout)) == 0) {

			return;
		}
		state->error = gfarm_errno_to_error(rv);
	}
	if (state->continuation != NULL)
		(*state->continuation)(state->closure);
}
