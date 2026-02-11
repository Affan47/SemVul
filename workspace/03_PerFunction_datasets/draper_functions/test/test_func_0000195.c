attempt_transfer(struct unistim_subchannel *p1, struct unistim_subchannel *p2)
{
	int res = 0;
	struct ast_channel
	 *chana = NULL, *chanb = NULL, *bridgea = NULL, *bridgeb = NULL, *peera =
		NULL, *peerb = NULL, *peerc = NULL, *peerd = NULL;

	if (!p1->owner || !p2->owner) {
		ast_log(LOG_WARNING, "Transfer attempted without dual ownership?\n");
		return -1;
	}
	chana = p1->owner;
	chanb = p2->owner;
	bridgea = ast_bridged_channel(chana);
	bridgeb = ast_bridged_channel(chanb);

	if (bridgea) {
		peera = chana;
		peerb = chanb;
		peerc = bridgea;
		peerd = bridgeb;
	} else if (bridgeb) {
		peera = chanb;
		peerb = chana;
		peerc = bridgeb;
		peerd = bridgea;
	}

	if (peera && peerb && peerc && (peerb != peerc)) {
		unistim_quiet_chan(peera);
		unistim_quiet_chan(peerb);
		unistim_quiet_chan(peerc);
		if (peerd) {
			unistim_quiet_chan(peerd);
		}

		ast_log(LOG_NOTICE, "UNISTIM transfer: trying to masquerade %s into %s\n", ast_channel_name(peerc), ast_channel_name(peerb));
		if (ast_channel_masquerade(peerb, peerc)) {
			ast_log(LOG_WARNING, "Failed to masquerade %s into %s\n", ast_channel_name(peerb),
					ast_channel_name(peerc));
			res = -1;
		}
		return res;
	} else {
		ast_log(LOG_NOTICE,
				"Transfer attempted with no appropriate bridged calls to transfer\n");
		if (chana) {
			ast_softhangup_nolock(chana, AST_SOFTHANGUP_DEV);
		}
		if (chanb) {
			ast_softhangup_nolock(chanb, AST_SOFTHANGUP_DEV);
		}
		return -1;
	}
	return 0;
}
