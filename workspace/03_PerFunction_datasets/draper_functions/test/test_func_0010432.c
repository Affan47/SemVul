mwifiex_is_pattern_supported(struct cfg80211_pkt_pattern *pat, s8 *byte_seq,
			     u8 max_byte_seq)
{
	int j, k, valid_byte_cnt = 0;
	bool dont_care_byte = false;

	for (j = 0; j < DIV_ROUND_UP(pat->pattern_len, 8); j++) {
		for (k = 0; k < 8; k++) {
			if (pat->mask[j] & 1 << k) {
				memcpy(byte_seq + valid_byte_cnt,
				       &pat->pattern[j * 8 + k], 1);
				valid_byte_cnt++;
				if (dont_care_byte)
					return false;
			} else {
				if (valid_byte_cnt)
					dont_care_byte = true;
			}

			if (valid_byte_cnt > max_byte_seq)
				return false;
		}
	}

	byte_seq[max_byte_seq] = valid_byte_cnt;

	return true;
}
