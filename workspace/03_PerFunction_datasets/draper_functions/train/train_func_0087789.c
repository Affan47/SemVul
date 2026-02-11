iw4965_is_ht40_channel(__le32 rxon_flags)
{
	int chan_mod =
	    le32_to_cpu(rxon_flags & RXON_FLG_CHANNEL_MODE_MSK) >>
	    RXON_FLG_CHANNEL_MODE_POS;
	return (chan_mod == CHANNEL_MODE_PURE_40 ||
		chan_mod == CHANNEL_MODE_MIXED);
}
