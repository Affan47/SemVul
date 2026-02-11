uwb_rsv_terminate(struct uwb_rsv *rsv)
{
	struct uwb_rc *rc = rsv->rc;

	mutex_lock(&rc->rsvs_mutex);

	if (rsv->state != UWB_RSV_STATE_NONE)
		uwb_rsv_set_state(rsv, UWB_RSV_STATE_NONE);

	mutex_unlock(&rc->rsvs_mutex);
}
