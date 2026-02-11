handle_pending_uuids(uint16_t index)
{
	struct controller_info *info;
	struct pending_uuid *pending;

	DBG("index %d", index);

	info = &controllers[index];

	info->pending_uuid = FALSE;

	if (g_slist_length(info->pending_uuids) == 0) {
		if (info->pending_class) {
			info->pending_class = FALSE;
			mgmt_set_dev_class(index, info->major, info->minor);
		}

		if (info->pending_powered) {
			info->pending_powered = FALSE;
			mgmt_set_powered(index, TRUE);
		}

		return;
	}

	pending = info->pending_uuids->data;

	mgmt_add_uuid(index, &pending->uuid, pending->svc_hint);

	info->pending_uuids = g_slist_remove(info->pending_uuids, pending);
	g_free(pending);
}
