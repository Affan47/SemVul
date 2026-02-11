gather_softmix_stats(struct softmix_stats *stats,
	const struct softmix_bridge_data *softmix_data,
	struct ast_bridge_channel *bridge_channel)
{
	int channel_native_rate;
	int i;

	channel_native_rate = MAX(ast_format_rate(ast_channel_rawwriteformat(bridge_channel->chan)),
		ast_format_rate(ast_channel_rawreadformat(bridge_channel->chan)));

	if (channel_native_rate > stats->highest_supported_rate) {
		stats->highest_supported_rate = channel_native_rate;
	}
	if (channel_native_rate > softmix_data->internal_rate) {
		for (i = 0; i < ARRAY_LEN(stats->sample_rates); i++) {
			if (stats->sample_rates[i] == channel_native_rate) {
				stats->num_channels[i]++;
				break;
			} else if (!stats->sample_rates[i]) {
				stats->sample_rates[i] = channel_native_rate;
				stats->num_channels[i]++;
				break;
			}
		}
		stats->num_above_internal_rate++;
	} else if (channel_native_rate == softmix_data->internal_rate) {
		stats->num_at_internal_rate++;
	}
}
