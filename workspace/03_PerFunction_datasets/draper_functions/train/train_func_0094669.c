aim_getcap(aim_session_t *sess, aim_bstream_t *bs, int len)
{
	fu32_t flags = 0;
	int offset;

	for (offset = 0; aim_bstream_empty(bs) && (offset < len);
		offset += 0x10) {
		fu8_t *cap;
		int i, identified;

		cap = aimbs_getraw(bs, 0x10);

		for (i = 0, identified = 0; !(aim_caps[i].flag & AIM_CAPS_LAST);
			i++) {

			if (memcmp(&aim_caps[i].data, cap, 0x10) == 0) {
				flags |= aim_caps[i].flag;
				identified++;
				break;

			}
		}

		if (!identified) {
			faimdprintf(sess, 0,
				"unknown capability: {%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x}\n",
				cap[0], cap[1], cap[2], cap[3], cap[4], cap[5],
				cap[6], cap[7], cap[8], cap[9], cap[10],
				cap[11], cap[12], cap[13], cap[14], cap[15]);
		}

		free(cap);
	}

	return flags;
}
