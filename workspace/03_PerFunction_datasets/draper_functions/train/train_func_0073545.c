efx_mcdi_mon_show_alarm(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	struct efx_mcdi_mon_attribute *mon_attr =
		container_of(attr, struct efx_mcdi_mon_attribute, dev_attr);
	efx_dword_t entry;
	int state;
	int rc;

	rc = efx_mcdi_mon_get_entry(dev, mon_attr->index, &entry);
	if (rc)
		return rc;

	state = EFX_DWORD_FIELD(entry, MC_CMD_SENSOR_VALUE_ENTRY_TYPEDEF_STATE);
	return sprintf(buf, "%d\n", state != MC_CMD_SENSOR_STATE_OK);
}
