ahd_match_scb(struct ahd_softc *ahd, struct scb *scb, int target,
	      char channel, int lun, u_int tag, role_t role)
{
	int targ = SCB_GET_TARGET(ahd, scb);
	char chan = SCB_GET_CHANNEL(ahd, scb);
	int slun = SCB_GET_LUN(scb);
	int match;

	match = ((chan == channel) || (channel == ALL_CHANNELS));
	if (match != 0)
		match = ((targ == target) || (target == CAM_TARGET_WILDCARD));
	if (match != 0)
		match = ((lun == slun) || (lun == CAM_LUN_WILDCARD));
	if (match != 0) {
#ifdef AHD_TARGET_MODE
		int group;

		group = XPT_FC_GROUP(scb->io_ctx->ccb_h.func_code);
		if (role == ROLE_INITIATOR) {
			match = (group != XPT_FC_GROUP_TMODE)
			      && ((tag == SCB_GET_TAG(scb))
			       || (tag == SCB_LIST_NULL));
		} else if (role == ROLE_TARGET) {
			match = (group == XPT_FC_GROUP_TMODE)
			      && ((tag == scb->io_ctx->csio.tag_id)
			       || (tag == SCB_LIST_NULL));
		}
#else
		match = ((tag == SCB_GET_TAG(scb)) || (tag == SCB_LIST_NULL));
#endif
	}

	return match;
}
