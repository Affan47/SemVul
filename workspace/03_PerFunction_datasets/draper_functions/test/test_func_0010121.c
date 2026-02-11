do_schannels(struct cmd_context *ctx)
{
	struct ethtool_channels echannels;
	int gchannels_changed;
	s32 channels_rx_wanted = -1;
	s32 channels_tx_wanted = -1;
	s32 channels_other_wanted = -1;
	s32 channels_combined_wanted = -1;
	struct cmdline_info cmdline_channels[] = {
		{ "rx", CMDL_S32, &channels_rx_wanted, &echannels.rx_count },
		{ "tx", CMDL_S32, &channels_tx_wanted, &echannels.tx_count },
		{ "other", CMDL_S32, &channels_other_wanted,
		  &echannels.other_count },
		{ "combined", CMDL_S32, &channels_combined_wanted,
		  &echannels.combined_count },
	};
	int err, changed = 0;

	parse_generic_cmdline(ctx, &gchannels_changed,
			      cmdline_channels, ARRAY_SIZE(cmdline_channels));

	echannels.cmd = ETHTOOL_GCHANNELS;
	err = send_ioctl(ctx, &echannels);
	if (err) {
		perror("Cannot get device channel parameters");
		return 1;
	}

	do_generic_set(cmdline_channels, ARRAY_SIZE(cmdline_channels),
			&changed);

	if (!changed) {
		fprintf(stderr, "no channel parameters changed, aborting\n");
		fprintf(stderr, "current values: tx %u rx %u other %u"
			"combined %u\n", echannels.rx_count,
			echannels.tx_count, echannels.other_count,
			echannels.combined_count);
		return 1;
	}

	echannels.cmd = ETHTOOL_SCHANNELS;
	err = send_ioctl(ctx, &echannels);
	if (err) {
		perror("Cannot set device channel parameters");
		return 1;
	}

	return 0;
}
