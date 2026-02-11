ipmi_lan_set_vlan_priority(struct ipmi_intf * intf,  uint8_t chan, char *string)
{
	uint8_t data;
	int rc;
	int priority = atoi(string);

	if (priority < 0 || priority > 7) {
		lprintf(LOG_NOTICE, "vlan priority must be between 0 and 7.");
		return -1;
	}
	data = (uint8_t)priority;
	rc = set_lan_param(intf, chan, IPMI_LANP_VLAN_PRIORITY, &data, 1);
	return rc;
}
