ipmi_lan_set_vlan_id(struct ipmi_intf * intf,  uint8_t chan, char *string)
{
	uint8_t data[2];
	int rc;

	if (string == NULL) {
		data[0] = 0;
		data[1] = 0;
	}
	else {
		int id = atoi(string);

		if (id < 1 || id > 4094) {
			lprintf(LOG_NOTICE, "vlan id must be between 1 and 4094.");
			return -1;
		}
		else {
			data[0] = (uint8_t)id;
			data[1] = (uint8_t)(id >> 8) | 0x80;
		}
	}
	rc = set_lan_param(intf, chan, IPMI_LANP_VLAN_ID, data, 2);
	return rc;
}
