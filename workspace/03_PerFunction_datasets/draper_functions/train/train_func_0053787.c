thermal_set_governor(struct thermal_zone_device *tz,
				struct thermal_governor *new_gov)
{
	int ret = 0;

	if (tz->governor && tz->governor->unbind_from_tz)
		tz->governor->unbind_from_tz(tz);

	if (new_gov && new_gov->bind_to_tz) {
		ret = new_gov->bind_to_tz(tz);
		if (ret) {
			bind_previous_governor(tz, new_gov->name);

			return ret;
		}
	}

	tz->governor = new_gov;

	return ret;
}
