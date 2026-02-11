thermal_unregister_governor(struct thermal_governor *governor)
{
	struct thermal_zone_device *pos;

	if (!governor)
		return;

	mutex_lock(&thermal_governor_lock);

	if (__find_governor(governor->name) == NULL)
		goto exit;

	mutex_lock(&thermal_list_lock);

	list_for_each_entry(pos, &thermal_tz_list, node) {
		if (!strncasecmp(pos->governor->name, governor->name,
						THERMAL_NAME_LENGTH))
			thermal_set_governor(pos, NULL);
	}

	mutex_unlock(&thermal_list_lock);
	list_del(&governor->governor_list);
exit:
	mutex_unlock(&thermal_governor_lock);
	return;
}
