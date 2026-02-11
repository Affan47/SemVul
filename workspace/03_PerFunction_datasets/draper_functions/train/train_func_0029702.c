fill_txdesc_phy(struct pkt_attrib *pattrib, __le32 *pdw)
{
	if (pattrib->ht_en) {
		*pdw |= (pattrib->bwmode&HT_CHANNEL_WIDTH_40) ?	cpu_to_le32(BIT(25)) : 0;

		if (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_LOWER)
			*pdw |= cpu_to_le32((0x01 << DATA_SC_SHT) & 0x003f0000);
		else if (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_UPPER)
			*pdw |= cpu_to_le32((0x02 << DATA_SC_SHT) & 0x003f0000);
		else if (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_DONT_CARE)
			*pdw |= 0;
		else
			*pdw |= cpu_to_le32((0x03 << DATA_SC_SHT) & 0x003f0000);
	}
}
