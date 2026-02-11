gfm_server_pio_set_paths(struct peer *peer, int from_client, int skip)
{
	gfarm_error_t e;
	static const char diag[] = "GFM_PROTO_PIO_SET_PATHS";


	gflog_error(GFARM_MSG_1000395, "%s: not implemented", diag);

	e = gfm_server_put_reply(peer, diag,
	    GFARM_ERR_FUNCTION_NOT_IMPLEMENTED, "");
	return (e != GFARM_ERR_NO_ERROR ? e :
	    GFARM_ERR_FUNCTION_NOT_IMPLEMENTED);
}
