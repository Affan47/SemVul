gf_rtp_parse_h263(GF_RTPDepacketizer *rtp, GF_RTPHeader *hdr, char *payload, u32 size)
{
	GF_BitStream *bs;
	Bool P_bit, V_bit;
	u32 plen;
	u64 offset;
	char blank[2];

	bs = gf_bs_new(payload, size, GF_BITSTREAM_READ);

	gf_bs_read_int(bs, 5);
	P_bit = gf_bs_read_int(bs, 1);
	V_bit = gf_bs_read_int(bs, 1);
	plen = gf_bs_read_int(bs, 6);
	gf_bs_read_int(bs, 3);


	if (V_bit) {
		gf_bs_read_u8(bs);
	}

	if (plen) {
		gf_bs_skip_bytes(bs, plen);
	}
	offset = gf_bs_get_position(bs);
	gf_bs_del(bs);

	blank[0] = blank[1] = 0;

	if (P_bit) {
		rtp->sl_hdr.compositionTimeStamp = hdr->TimeStamp;
		rtp->sl_hdr.compositionTimeStampFlag = 1;
		rtp->sl_hdr.accessUnitStartFlag = 1;
		rtp->sl_hdr.accessUnitEndFlag = 0;

		if (rtp->sl_hdr.accessUnitStartFlag) {

			rtp->sl_hdr.randomAccessPointFlag = (payload[offset+2]&0x02) ? 0 : 1;
		}

		rtp->on_sl_packet(rtp->udta, (char *) blank, 2, &rtp->sl_hdr, GF_OK);

		rtp->sl_hdr.compositionTimeStampFlag = 0;
		rtp->sl_hdr.accessUnitStartFlag = 0;
		rtp->sl_hdr.randomAccessPointFlag = 0;


		rtp->sl_hdr.accessUnitEndFlag = hdr->Marker;
		rtp->on_sl_packet(rtp->udta, payload + offset, (u32) (size - offset), &rtp->sl_hdr, GF_OK);
	} else {

		rtp->sl_hdr.accessUnitEndFlag = hdr->Marker;
		rtp->on_sl_packet(rtp->udta, payload + offset, (u32) (size - offset), &rtp->sl_hdr, GF_OK);
	}
}
