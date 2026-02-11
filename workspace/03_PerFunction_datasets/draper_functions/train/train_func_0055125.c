set_conf(struct userdata *u)
{
	union {
		struct bt_set_configuration_req setconf_req;
		struct bt_set_configuration_rsp setconf_rsp;
		bt_audio_error_t error;
		uint8_t buf[BT_SUGGESTED_BUFFER_SIZE];
	} msg;

	if (u->transport == BT_CAPABILITIES_TRANSPORT_A2DP) {
		if (setup_a2dp(u) < 0)
			return -1;
	}

	memset(&msg, 0, sizeof(msg));
	msg.setconf_req.h.type = BT_REQUEST;
	msg.setconf_req.h.name = BT_SET_CONFIGURATION;
	msg.setconf_req.h.length = sizeof(msg.setconf_req);

	if (u->transport == BT_CAPABILITIES_TRANSPORT_A2DP) {
		memcpy(&msg.setconf_req.codec, &u->a2dp.sbc_capabilities,
			sizeof(u->a2dp.sbc_capabilities));
		msg.setconf_req.h.length += msg.setconf_req.codec.length -
			sizeof(msg.setconf_req.codec);
	} else {
		msg.setconf_req.codec.transport = BT_CAPABILITIES_TRANSPORT_SCO;
		msg.setconf_req.codec.seid = BT_A2DP_SEID_RANGE + 1;
		msg.setconf_req.codec.length = sizeof(pcm_capabilities_t);
	}

	if (service_send(u, &msg.setconf_req.h) < 0)
		return -1;

	msg.setconf_rsp.h.length = sizeof(msg.setconf_rsp);
	if (service_expect(u, &msg.setconf_rsp.h, BT_SET_CONFIGURATION) < 0)
		return -1;

	u->link_mtu = msg.setconf_rsp.link_mtu;


	if (u->transport == BT_CAPABILITIES_TRANSPORT_A2DP) {
		setup_sbc(&u->a2dp);
		u->block_size = u->a2dp.codesize;
		DBG("SBC parameters:\n\tallocation=%u\n"
			"\tsubbands=%u\n\tblocks=%u\n\tbitpool=%u\n",
			u->a2dp.sbc.allocation, u->a2dp.sbc.subbands,
			u->a2dp.sbc.blocks, u->a2dp.sbc.bitpool);
	} else
		u->block_size = u->link_mtu;

	return 0;
}
