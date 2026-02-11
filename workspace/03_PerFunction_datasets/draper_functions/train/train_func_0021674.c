uwb_rsv_remove(struct uwb_rsv *rsv)
{
	uwb_rsv_dump("RM", rsv);

	if (rsv->state != UWB_RSV_STATE_NONE)
		uwb_rsv_set_state(rsv, UWB_RSV_STATE_NONE);

	if (rsv->needs_release_companion_mas)
		uwb_drp_avail_release(rsv->rc, &rsv->mv.companion_mas);
	uwb_drp_avail_release(rsv->rc, &rsv->mas);

	if (uwb_rsv_is_owner(rsv))
		uwb_rsv_put_stream(rsv);

	uwb_dev_put(rsv->owner);
	if (rsv->target.type == UWB_RSV_TARGET_DEV)
		uwb_dev_put(rsv->target.dev);

	list_del_init(&rsv->rc_node);
	uwb_rsv_put(rsv);
}
