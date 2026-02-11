get_cap_info(u8 *data)
{
	u16 cap_info = 0;
	u16 index    = MAC_HDR_LEN;
	enum sub_frame_type st;

	st = get_sub_type(data);


	if ((st == BEACON) || (st == PROBE_RSP))
		index += TIME_STAMP_LEN + BEACON_INTERVAL_LEN;

	cap_info  = data[index];
	cap_info |= (data[index + 1] << 8);

	return cap_info;
}
