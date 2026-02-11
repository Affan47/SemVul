icq_send_msg_ch1(session_t *session, const char *uid, const char *message) {
	string_t pkt;
	string_t tlv_2, tlv_101;
	userlist_t *u = userlist_find(session, uid);
	uint16_t enc = 0;
	const char *tmp = message;

	while (*tmp) {
		if ((*tmp++ & 0x80)) {
			enc = 2;
			break;
		}
	}
	if ( enc && !(u && user_private_item_get_int(u, "utf")) )
		enc = 3;


	tlv_101 = icq_pack("WW", enc, 0x00);
	if (enc == 2) {

		string_t recode = icq_convert_to_ucs2be((char *) message);
		string_append_raw(tlv_101, recode->str, recode->len);
		string_free(recode, 1);
	} else {

		string_append(tlv_101, message);
	}


	tlv_2 = icq_pack("tcT",
				icq_pack_tlv_char(0x501, 0x1),
				icq_pack_tlv(0x0101, tlv_101->str, tlv_101->len)
			);
	string_free(tlv_101, 1);


	pkt = icq_pack("iiWs", (uint32_t) rand(), (uint32_t) rand(), 1, uid+4);
	icq_pack_append(pkt, "TTT",
				icq_pack_tlv(0x02, tlv_2->str, tlv_2->len),
				icq_pack_tlv(0x03, NULL, 0),
				icq_pack_tlv(0x06, NULL, 0)
				);

	string_free(tlv_2, 1);


	icq_makesnac(session, pkt, 0x04, 0x06, NULL, NULL);
	icq_send_pkt(session, pkt);
}
