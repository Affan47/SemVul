skl_create_channel_map(enum skl_ch_cfg ch_cfg)
{
	u32 config;

	switch (ch_cfg) {
	case SKL_CH_CFG_MONO:
		config =  (0xFFFFFFF0 | SKL_CHANNEL_LEFT);
		break;

	case SKL_CH_CFG_STEREO:
		config = (0xFFFFFF00 | SKL_CHANNEL_LEFT
			| (SKL_CHANNEL_RIGHT << 4));
		break;

	case SKL_CH_CFG_2_1:
		config = (0xFFFFF000 | SKL_CHANNEL_LEFT
			| (SKL_CHANNEL_RIGHT << 4)
			| (SKL_CHANNEL_LFE << 8));
		break;

	case SKL_CH_CFG_3_0:
		config =  (0xFFFFF000 | SKL_CHANNEL_LEFT
			| (SKL_CHANNEL_CENTER << 4)
			| (SKL_CHANNEL_RIGHT << 8));
		break;

	case SKL_CH_CFG_3_1:
		config = (0xFFFF0000 | SKL_CHANNEL_LEFT
			| (SKL_CHANNEL_CENTER << 4)
			| (SKL_CHANNEL_RIGHT << 8)
			| (SKL_CHANNEL_LFE << 12));
		break;

	case SKL_CH_CFG_QUATRO:
		config = (0xFFFF0000 | SKL_CHANNEL_LEFT
			| (SKL_CHANNEL_RIGHT << 4)
			| (SKL_CHANNEL_LEFT_SURROUND << 8)
			| (SKL_CHANNEL_RIGHT_SURROUND << 12));
		break;

	case SKL_CH_CFG_4_0:
		config = (0xFFFF0000 | SKL_CHANNEL_LEFT
			| (SKL_CHANNEL_CENTER << 4)
			| (SKL_CHANNEL_RIGHT << 8)
			| (SKL_CHANNEL_CENTER_SURROUND << 12));
		break;

	case SKL_CH_CFG_5_0:
		config = (0xFFF00000 | SKL_CHANNEL_LEFT
			| (SKL_CHANNEL_CENTER << 4)
			| (SKL_CHANNEL_RIGHT << 8)
			| (SKL_CHANNEL_LEFT_SURROUND << 12)
			| (SKL_CHANNEL_RIGHT_SURROUND << 16));
		break;

	case SKL_CH_CFG_5_1:
		config = (0xFF000000 | SKL_CHANNEL_CENTER
			| (SKL_CHANNEL_LEFT << 4)
			| (SKL_CHANNEL_RIGHT << 8)
			| (SKL_CHANNEL_LEFT_SURROUND << 12)
			| (SKL_CHANNEL_RIGHT_SURROUND << 16)
			| (SKL_CHANNEL_LFE << 20));
		break;

	case SKL_CH_CFG_DUAL_MONO:
		config = (0xFFFFFF00 | SKL_CHANNEL_LEFT
			| (SKL_CHANNEL_LEFT << 4));
		break;

	case SKL_CH_CFG_I2S_DUAL_STEREO_0:
		config = (0xFFFFFF00 | SKL_CHANNEL_LEFT
			| (SKL_CHANNEL_RIGHT << 4));
		break;

	case SKL_CH_CFG_I2S_DUAL_STEREO_1:
		config = (0xFFFF00FF | (SKL_CHANNEL_LEFT << 8)
			| (SKL_CHANNEL_RIGHT << 12));
		break;

	default:
		config =  0xFFFFFFFF;
		break;

	}

	return config;
}
