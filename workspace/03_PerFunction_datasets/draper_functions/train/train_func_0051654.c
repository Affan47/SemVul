ipmi_set_power_capstatus_command(struct ipmi_intf * intf, uint8_t val)
{
	struct ipmi_rs * rsp = NULL;
	struct ipmi_rq req = {0};
	uint8_t data[2];
	if (ipmi_get_power_capstatus_command(intf) < 0) {
		return -1;
	}
	if (PowercapSetable_flag != 1) {
		lprintf(LOG_ERR, "Can not set powercap on this system");
		return -1;
	}
	req.msg.netfn = DELL_OEM_NETFN;
	req.msg.lun = 0;
	req.msg.cmd = IPMI_DELL_POWER_CAP_STATUS;
	req.msg.data_len = 2;
	req.msg.data = data;
	data[0] = 00;
	data[1] = val;
	rsp = intf->sendrecv(intf, &req);
	if (rsp == NULL) {
		lprintf(LOG_ERR, "Error setting powercap status");
		return -1;
	} else if ((iDRAC_FLAG == IDRAC_12G) && (rsp->ccode == LICENSE_NOT_SUPPORTED)) {
		lprintf(LOG_ERR,
				"FM001 : A required license is missing or expired");
		return -1;
	} else if (rsp->ccode > 0) {
		lprintf(LOG_ERR, "Error setting powercap statusr: %s",
				val2str(rsp->ccode, completion_code_vals));
		return -1;
	}
	return 0;
}
