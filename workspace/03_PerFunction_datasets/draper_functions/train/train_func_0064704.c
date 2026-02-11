csio_lnode_state_to_str(struct csio_lnode *ln, int8_t *str)
{
	if (csio_get_state(ln) == ((csio_sm_state_t)csio_lns_uninit)) {
		strcpy(str, "UNINIT");
		return;
	}
	if (csio_get_state(ln) == ((csio_sm_state_t)csio_lns_ready)) {
		strcpy(str, "READY");
		return;
	}
	if (csio_get_state(ln) == ((csio_sm_state_t)csio_lns_offline)) {
		strcpy(str, "OFFLINE");
		return;
	}
	strcpy(str, "UNKNOWN");
}
