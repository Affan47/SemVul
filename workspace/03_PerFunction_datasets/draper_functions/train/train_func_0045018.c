il3945_get_measurement(struct il_priv *il,
		       struct ieee80211_measurement_params *params, u8 type)
{
	struct il_spectrum_cmd spectrum;
	struct il_rx_pkt *pkt;
	struct il_host_cmd cmd = {
		.id = C_SPECTRUM_MEASUREMENT,
		.data = (void *)&spectrum,
		.flags = CMD_WANT_SKB,
	};
	u32 add_time = le64_to_cpu(params->start_time);
	int rc;
	int spectrum_resp_status;
	int duration = le16_to_cpu(params->duration);

	if (il_is_associated(il))
		add_time =
		    il_usecs_to_beacons(il,
					le64_to_cpu(params->start_time) -
					il->_3945.last_tsf,
					le16_to_cpu(il->timing.beacon_interval));

	memset(&spectrum, 0, sizeof(spectrum));

	spectrum.channel_count = cpu_to_le16(1);
	spectrum.flags =
	    RXON_FLG_TSF2HOST_MSK | RXON_FLG_ANT_A_MSK | RXON_FLG_DIS_DIV_MSK;
	spectrum.filter_flags = MEASUREMENT_FILTER_FLAG;
	cmd.len = sizeof(spectrum);
	spectrum.len = cpu_to_le16(cmd.len - sizeof(spectrum.len));

	if (il_is_associated(il))
		spectrum.start_time =
		    il_add_beacon_time(il, il->_3945.last_beacon_time, add_time,
				       le16_to_cpu(il->timing.beacon_interval));
	else
		spectrum.start_time = 0;

	spectrum.channels[0].duration = cpu_to_le32(duration * TIME_UNIT);
	spectrum.channels[0].channel = params->channel;
	spectrum.channels[0].type = type;
	if (il->active.flags & RXON_FLG_BAND_24G_MSK)
		spectrum.flags |=
		    RXON_FLG_BAND_24G_MSK | RXON_FLG_AUTO_DETECT_MSK |
		    RXON_FLG_TGG_PROTECT_MSK;

	rc = il_send_cmd_sync(il, &cmd);
	if (rc)
		return rc;

	pkt = (struct il_rx_pkt *)cmd.reply_page;
	if (pkt->hdr.flags & IL_CMD_FAILED_MSK) {
		IL_ERR("Bad return from N_RX_ON_ASSOC command\n");
		rc = -EIO;
	}

	spectrum_resp_status = le16_to_cpu(pkt->u.spectrum.status);
	switch (spectrum_resp_status) {
	case 0:
		if (pkt->u.spectrum.id != 0xff) {
			D_INFO("Replaced existing measurement: %d\n",
			       pkt->u.spectrum.id);
			il->measurement_status &= ~MEASUREMENT_READY;
		}
		il->measurement_status |= MEASUREMENT_ACTIVE;
		rc = 0;
		break;

	case 1:
		rc = -EAGAIN;
		break;
	}

	il_free_pages(il, cmd.reply_page);

	return rc;
}
