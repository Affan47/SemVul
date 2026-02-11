show_dock_type(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct dock_station *dock_station = dev->platform_data;
	char *type;

	if (dock_station->flags & DOCK_IS_DOCK)
		type = "dock_station";
	else if (dock_station->flags & DOCK_IS_ATA)
		type = "ata_bay";
	else if (dock_station->flags & DOCK_IS_BAT)
		type = "battery_bay";
	else
		type = "unknown";

	return snprintf(buf, PAGE_SIZE, "%s\n", type);
}
