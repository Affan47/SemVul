ipmi_sdr_get_sensor_thresholds(struct ipmi_intf *intf, uint8_t sensor,
					uint8_t target, uint8_t lun, uint8_t channel)
{
	struct ipmi_rq req;
	struct ipmi_rs *rsp;
	uint8_t  bridged_request = 0;
	uint32_t save_addr;
	uint32_t save_channel;

	if ( BRIDGE_TO_SENSOR(intf, target, channel) ) {
		bridged_request = 1;
		save_addr = intf->target_addr;
		intf->target_addr = target;
		save_channel = intf->target_channel;
		intf->target_channel = channel;
	}

	memset(&req, 0, sizeof (req));
	req.msg.netfn = IPMI_NETFN_SE;
	req.msg.lun = lun;
	req.msg.cmd = GET_SENSOR_THRESHOLDS;
	req.msg.data = &sensor;
	req.msg.data_len = sizeof (sensor);

	rsp = intf->sendrecv(intf, &req);
	if (bridged_request) {
		intf->target_addr = save_addr;
		intf->target_channel = save_channel;
	}
	return rsp;
}
