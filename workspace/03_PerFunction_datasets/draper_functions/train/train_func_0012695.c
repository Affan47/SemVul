efx_ptp_rx(struct efx_channel *channel, struct sk_buff *skb)
{
	struct efx_nic *efx = channel->efx;
	struct efx_ptp_data *ptp = efx->ptp_data;
	struct efx_ptp_match *match = (struct efx_ptp_match *)skb->cb;
	u8 *match_data_012, *match_data_345;
	unsigned int version;
	u8 *data;

	match->expiry = jiffies + msecs_to_jiffies(PKT_EVENT_LIFETIME_MS);


	if (ptp->mode == MC_CMD_PTP_MODE_V1) {
		if (!pskb_may_pull(skb, PTP_V1_MIN_LENGTH)) {
			return false;
		}
		data = skb->data;
		version = ntohs(*(__be16 *)&data[PTP_V1_VERSION_OFFSET]);
		if (version != PTP_VERSION_V1) {
			return false;
		}


		match_data_012 = data + PTP_V1_UUID_OFFSET;
		match_data_345 = data + PTP_V1_UUID_OFFSET + 3;
	} else {
		if (!pskb_may_pull(skb, PTP_V2_MIN_LENGTH)) {
			return false;
		}
		data = skb->data;
		version = data[PTP_V2_VERSION_OFFSET];
		if ((version & PTP_VERSION_V2_MASK) != PTP_VERSION_V2) {
			return false;
		}


		match_data_345 = data + PTP_V2_UUID_OFFSET + 5;
		if (ptp->mode == MC_CMD_PTP_MODE_V2) {
			match_data_012 = data + PTP_V2_UUID_OFFSET + 2;
		} else {
			match_data_012 = data + PTP_V2_UUID_OFFSET + 0;
			BUG_ON(ptp->mode != MC_CMD_PTP_MODE_V2_ENHANCED);
		}
	}


	if (ntohs(*(__be16 *)&data[PTP_DPORT_OFFSET]) == PTP_EVENT_PORT) {
		match->state = PTP_PACKET_STATE_UNMATCHED;


		BUILD_BUG_ON(PTP_V1_SEQUENCE_OFFSET != PTP_V2_SEQUENCE_OFFSET);
		BUILD_BUG_ON(PTP_V1_SEQUENCE_LENGTH != PTP_V2_SEQUENCE_LENGTH);


		match->words[0] = (match_data_012[0]         |
				   (match_data_012[1] << 8)  |
				   (match_data_012[2] << 16) |
				   (match_data_345[0] << 24));
		match->words[1] = (match_data_345[1]         |
				   (match_data_345[2] << 8)  |
				   (data[PTP_V1_SEQUENCE_OFFSET +
					 PTP_V1_SEQUENCE_LENGTH - 1] <<
				    16));
	} else {
		match->state = PTP_PACKET_STATE_MATCH_UNWANTED;
	}

	skb_queue_tail(&ptp->rxq, skb);
	queue_work(ptp->workwq, &ptp->work);

	return true;
}
