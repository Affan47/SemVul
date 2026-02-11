recheck_killswitches (NMUdevManager *self)
{
	NMUdevManagerPrivate *priv = NM_UDEV_MANAGER_GET_PRIVATE (self);
	GSList *iter;
	RfKillState poll_states[RFKILL_TYPE_MAX];
	RfKillState platform_states[RFKILL_TYPE_MAX];
	gboolean platform_checked[RFKILL_TYPE_MAX];
	int i;


	for (i = 0; i < RFKILL_TYPE_MAX; i++) {
		poll_states[i] = RFKILL_UNBLOCKED;
		platform_states[i] = RFKILL_UNBLOCKED;
		platform_checked[i] = FALSE;
	}


	for (iter = priv->killswitches; iter; iter = g_slist_next (iter)) {
		Killswitch *ks = iter->data;
		GUdevDevice *device;
		RfKillState dev_state;
		int sysfs_state;

		device = g_udev_client_query_by_subsystem_and_name (priv->client, "rfkill", ks->name);
		if (device) {
			sysfs_state = g_udev_device_get_property_as_int (device, "RFKILL_STATE");
			dev_state = sysfs_state_to_nm_state (sysfs_state);

			nm_log_dbg (LOGD_RFKILL, "%s rfkill%s switch %s state now %d/%u",
			            rfkill_type_to_desc (ks->rtype),
			            ks->platform ? " platform" : "",
			            ks->name,
			            sysfs_state,
			            dev_state);

			if (ks->platform == FALSE) {
				if (dev_state > poll_states[ks->rtype])
					poll_states[ks->rtype] = dev_state;
			} else {
				platform_checked[ks->rtype] = TRUE;
				if (dev_state > platform_states[ks->rtype])
					platform_states[ks->rtype] = dev_state;
			}
			g_object_unref (device);
		}
	}


	for (i = 0; i < RFKILL_TYPE_MAX; i++) {
		if (platform_checked[i] == TRUE) {


			if (platform_states[i] != RFKILL_UNBLOCKED)
				poll_states[i] = platform_states[i];
		}

		if (poll_states[i] != priv->rfkill_states[i]) {
			nm_log_dbg (LOGD_RFKILL, "%s rfkill state now '%s'",
			            rfkill_type_to_desc (i),
			            rfkill_state_to_desc (poll_states[i]));

			priv->rfkill_states[i] = poll_states[i];
			g_signal_emit (self, signals[RFKILL_CHANGED], 0, i, priv->rfkill_states[i]);
		}
	}
}
