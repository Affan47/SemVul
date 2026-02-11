show_control_state(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	if (lighting_control_state == LEGACY_BOOTING)
		return scnprintf(buf, PAGE_SIZE, "[booting] running suspend\n");
	else if (lighting_control_state == LEGACY_SUSPEND)
		return scnprintf(buf, PAGE_SIZE, "booting running [suspend]\n");
	return scnprintf(buf, PAGE_SIZE, "booting [running] suspend\n");
}
