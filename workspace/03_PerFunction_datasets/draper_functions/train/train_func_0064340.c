fill_txdesc_sectype(struct pkt_attrib *pattrib, struct tx_desc *ptxdesc)
{
	if ((pattrib->encrypt > 0) && !pattrib->bswenc) {
		switch (pattrib->encrypt) {

		case _WEP40_:
		case _WEP104_:
			ptxdesc->txdw1 |= cpu_to_le32((0x01<<SEC_TYPE_SHT)&0x00c00000);
			ptxdesc->txdw2 |= cpu_to_le32(0x7 << AMPDU_DENSITY_SHT);
			break;
		case _TKIP_:
		case _TKIP_WTMIC_:
			ptxdesc->txdw1 |= cpu_to_le32((0x01<<SEC_TYPE_SHT)&0x00c00000);
			ptxdesc->txdw2 |= cpu_to_le32(0x7 << AMPDU_DENSITY_SHT);
			break;
		case _AES_:
			ptxdesc->txdw1 |= cpu_to_le32((0x03<<SEC_TYPE_SHT)&0x00c00000);
			ptxdesc->txdw2 |= cpu_to_le32(0x7 << AMPDU_DENSITY_SHT);
			break;
		case _NO_PRIVACY_:
		default:
			break;
		}
	}
}
