uwb_rsv_match(struct uwb_rsv *rsv, struct uwb_dev *src,
			  struct uwb_ie_drp *drp_ie)
{
	struct uwb_dev_addr *rsv_src;
	int stream;

	stream = uwb_ie_drp_stream_index(drp_ie);

	if (rsv->stream != stream)
		return false;

	switch (rsv->target.type) {
	case UWB_RSV_TARGET_DEVADDR:
		return rsv->stream == stream;
	case UWB_RSV_TARGET_DEV:
		if (uwb_ie_drp_owner(drp_ie))
			rsv_src = &rsv->owner->dev_addr;
		else
			rsv_src = &rsv->target.dev->dev_addr;
		return uwb_dev_addr_cmp(&src->dev_addr, rsv_src) == 0;
	}
	return false;
}
