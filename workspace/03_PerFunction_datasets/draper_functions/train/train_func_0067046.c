mgmt_set_powered(int index, gboolean powered)
{
	struct controller_info *info = &controllers[index];

	DBG("index %d powered %d pending_uuid %u", index, powered,
							info->pending_uuid);

	if (powered) {
		if (info->pending_uuid) {
			info->pending_powered = TRUE;
			return 0;
		}
	} else {
		info->pending_powered = FALSE;
	}

	return mgmt_set_mode(index, MGMT_OP_SET_POWERED, powered);
}
