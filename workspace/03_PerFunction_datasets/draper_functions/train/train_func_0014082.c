ast_rtp_instance_set_stats_vars(struct ast_channel *chan, struct ast_rtp_instance *instance)
{
	char quality_buf[AST_MAX_USER_FIELD], *quality;
	struct ast_channel *bridge = ast_bridged_channel(chan);

	if ((quality = ast_rtp_instance_get_quality(instance, AST_RTP_INSTANCE_STAT_FIELD_QUALITY, quality_buf, sizeof(quality_buf)))) {
		pbx_builtin_setvar_helper(chan, "RTPAUDIOQOS", quality);
		if (bridge) {
			pbx_builtin_setvar_helper(bridge, "RTPAUDIOQOSBRIDGED", quality);
		}
	}

	if ((quality = ast_rtp_instance_get_quality(instance, AST_RTP_INSTANCE_STAT_FIELD_QUALITY_JITTER, quality_buf, sizeof(quality_buf)))) {
		pbx_builtin_setvar_helper(chan, "RTPAUDIOQOSJITTER", quality);
		if (bridge) {
			pbx_builtin_setvar_helper(bridge, "RTPAUDIOQOSJITTERBRIDGED", quality);
		}
	}

	if ((quality = ast_rtp_instance_get_quality(instance, AST_RTP_INSTANCE_STAT_FIELD_QUALITY_LOSS, quality_buf, sizeof(quality_buf)))) {
		pbx_builtin_setvar_helper(chan, "RTPAUDIOQOSLOSS", quality);
		if (bridge) {
			pbx_builtin_setvar_helper(bridge, "RTPAUDIOQOSLOSSBRIDGED", quality);
		}
	}

	if ((quality = ast_rtp_instance_get_quality(instance, AST_RTP_INSTANCE_STAT_FIELD_QUALITY_RTT, quality_buf, sizeof(quality_buf)))) {
		pbx_builtin_setvar_helper(chan, "RTPAUDIOQOSRTT", quality);
		if (bridge) {
			pbx_builtin_setvar_helper(bridge, "RTPAUDIOQOSRTTBRIDGED", quality);
		}
	}
}
