r8712_efuse_map_write(struct _adapter *padapter, u16 addr, u16 cnts,
			 u8 *data)
{
	u8 offset, word_en, empty;
	u8 pktdata[PGPKT_DATA_SIZE], newdata[PGPKT_DATA_SIZE];
	int i, j, idx;

	if ((addr + cnts) > EFUSE_MAP_MAX_SIZE)
		return false;

	empty = r8712_read8(padapter, EFUSE_CLK_CTRL);
	if (empty != 0x03)
		return false;
	if (efuse_is_empty(padapter, &empty)) {
		if (empty)
			memset(pktdata, 0xFF, PGPKT_DATA_SIZE);
	} else {
		return false;
	}
	offset = (addr >> 3) & 0xF;
	if (!empty)
		if (!r8712_efuse_pg_packet_read(padapter, offset, pktdata))
			return false;
	word_en = 0xF;
	memset(newdata, 0xFF, PGPKT_DATA_SIZE);
	i = addr & 0x7;
	j = 0;
	idx = 0;

	if (i & 0x1) {

		if (data[idx] != pktdata[i]) {
			word_en &= ~BIT(i >> 1);
			newdata[j++] = pktdata[i - 1];
			newdata[j++] = data[idx];
		}
		i++;
		idx++;
	}
	do {
		for (; i < PGPKT_DATA_SIZE; i += 2) {
			if ((cnts - idx) == 1) {
				if (data[idx] != pktdata[i]) {
					word_en &= ~BIT(i >> 1);
					newdata[j++] = data[idx];
					newdata[j++] = pktdata[1 + 1];
				}
				idx++;
				break;
			}

			if ((data[idx] != pktdata[i]) || (data[idx + 1] !=
			     pktdata[i + 1])) {
				word_en &= ~BIT(i >> 1);
				newdata[j++] = data[idx];
				newdata[j++] = data[idx + 1];
			}
			idx += 2;

			if (idx == cnts)
				break;
		}

		if (word_en != 0xF)
			if (!r8712_efuse_pg_packet_write(padapter, offset,
							 word_en, newdata))
				return false;
		if (idx == cnts)
			break;
		offset++;
		if (!empty)
			if (!r8712_efuse_pg_packet_read(padapter, offset,
			    pktdata))
				return false;
		i = 0;
		j = 0;
		word_en = 0xF;
		memset(newdata, 0xFF, PGPKT_DATA_SIZE);
	} while (1);

	return true;
}
