authenticate(struct atmel_private *priv, u16 frame_len)
{
	struct auth_body *auth = (struct auth_body *)priv->rx_buf;
	u16 status = le16_to_cpu(auth->status);
	u16 trans_seq_no = le16_to_cpu(auth->trans_seq);
	u16 system = le16_to_cpu(auth->alg);

	if (status == WLAN_STATUS_SUCCESS && !priv->wep_is_on) {

		if (priv->station_was_associated) {
			atmel_enter_state(priv, STATION_STATE_REASSOCIATING);
			send_association_request(priv, 1);
			return;
		} else {
			atmel_enter_state(priv, STATION_STATE_ASSOCIATING);
			send_association_request(priv, 0);
			return;
		}
	}

	if (status == WLAN_STATUS_SUCCESS && priv->wep_is_on) {
		int should_associate = 0;

		if (trans_seq_no != priv->ExpectedAuthentTransactionSeqNum)
			return;

		if (system == WLAN_AUTH_OPEN) {
			if (trans_seq_no == 0x0002) {
				should_associate = 1;
			}
		} else if (system == WLAN_AUTH_SHARED_KEY) {
			if (trans_seq_no == 0x0002 &&
			    auth->el_id == WLAN_EID_CHALLENGE) {
				send_authentication_request(priv, system, auth->chall_text, auth->chall_text_len);
				return;
			} else if (trans_seq_no == 0x0004) {
				should_associate = 1;
			}
		}

		if (should_associate) {
			if (priv->station_was_associated) {
				atmel_enter_state(priv, STATION_STATE_REASSOCIATING);
				send_association_request(priv, 1);
				return;
			} else {
				atmel_enter_state(priv, STATION_STATE_ASSOCIATING);
				send_association_request(priv, 0);
				return;
			}
		}
	}

	if (status == WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG) {


		if (system == WLAN_AUTH_OPEN) {
			priv->CurrentAuthentTransactionSeqNum = 0x001;
			priv->exclude_unencrypted = 1;
			send_authentication_request(priv, WLAN_AUTH_SHARED_KEY, NULL, 0);
			return;
		} else if (system == WLAN_AUTH_SHARED_KEY
			   && priv->wep_is_on) {
			priv->CurrentAuthentTransactionSeqNum = 0x001;
			priv->exclude_unencrypted = 0;
			send_authentication_request(priv, WLAN_AUTH_OPEN, NULL, 0);
			return;
		} else if (priv->connect_to_any_BSS) {
			int bss_index;

			priv->BSSinfo[(int)(priv->current_BSS)].channel |= 0x80;

			if ((bss_index  = retrieve_bss(priv)) != -1) {
				atmel_join_bss(priv, bss_index);
				return;
			}
		}
	}

	priv->AuthenticationRequestRetryCnt = 0;
	atmel_enter_state(priv,  STATION_STATE_MGMT_ERROR);
	priv->station_is_associated = 0;
}
