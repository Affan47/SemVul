switch_congestion_setting(ib_portid_t * dest, char **argv, int argc)
{
	uint8_t rcv[IB_CC_DATA_SZ] = { 0 };
	uint8_t payload[IB_CC_DATA_SZ] = { 0 };
	uint32_t control_map;
	uint8_t victim_mask[32] = { 0 };
	uint8_t credit_mask[32] = { 0 };
	uint32_t threshold;
	uint32_t packet_size;
	uint32_t cs_threshold;
	uint32_t cs_returndelay_s;
	uint32_t cs_returndelay_m;
	uint32_t cs_returndelay;
	uint32_t marking_rate;
	char *errstr;

	if (argc != 8)
		return "invalid number of parameters for SwitchCongestionSetting";

	if ((errstr = parseint(argv[0], &control_map, 0)))
		return errstr;

	if ((errstr = parse256(argv[1], victim_mask)))
		return errstr;

	if ((errstr = parse256(argv[2], credit_mask)))
		return errstr;

	if ((errstr = parseint(argv[3], &threshold, 0)))
		return errstr;

	if ((errstr = parseint(argv[4], &packet_size, 0)))
		return errstr;

	if ((errstr = parseint(argv[5], &cs_threshold, 0)))
		return errstr;

	if ((errstr = parsecct(argv[6], &cs_returndelay_s, &cs_returndelay_m)))
		return errstr;

	cs_returndelay = cs_returndelay_m;
	cs_returndelay |= (cs_returndelay_s << 14);

	if ((errstr = parseint(argv[7], &marking_rate, 0)))
		return errstr;

	mad_encode_field(payload,
			 IB_CC_SWITCH_CONGESTION_SETTING_CONTROL_MAP_F,
			 &control_map);

	mad_set_array(payload,
		      0,
		      IB_CC_SWITCH_CONGESTION_SETTING_VICTIM_MASK_F,
		      victim_mask);

	mad_set_array(payload,
		      0,
		      IB_CC_SWITCH_CONGESTION_SETTING_CREDIT_MASK_F,
		      credit_mask);

	mad_encode_field(payload,
			 IB_CC_SWITCH_CONGESTION_SETTING_THRESHOLD_F,
			 &threshold);

	mad_encode_field(payload,
			 IB_CC_SWITCH_CONGESTION_SETTING_PACKET_SIZE_F,
			 &packet_size);

	mad_encode_field(payload,
			 IB_CC_SWITCH_CONGESTION_SETTING_CS_THRESHOLD_F,
			 &cs_threshold);

	mad_encode_field(payload,
			 IB_CC_SWITCH_CONGESTION_SETTING_CS_RETURN_DELAY_F,
			 &cs_returndelay);

	mad_encode_field(payload,
			 IB_CC_SWITCH_CONGESTION_SETTING_MARKING_RATE_F,
			 &marking_rate);

	if (!cc_config_status_via(payload, rcv, dest, IB_CC_ATTR_SWITCH_CONGESTION_SETTING,
				  0, 0, NULL, srcport, cckey))
		return "switch congestion setting config failed";

	return NULL;
}
