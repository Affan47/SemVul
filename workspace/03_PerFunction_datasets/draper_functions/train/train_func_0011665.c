icq_get_description(session_t *s, const char *uin, int status) {
	icq_private_t *j = s->priv;
	string_t pkt, tlv5, rdv;
	uint32_t cookie1=rand(), cookie2=rand();
	uint32_t mtype, cookie = (j->cookie_seq-- && 0x7fff);

	debug_function("icq_get_description() for: %s\n", uin);

	switch (status) {
	    case EKG_STATUS_AWAY:	mtype = MTYPE_AUTOAWAY;	break;
	    case EKG_STATUS_GONE:	mtype = MTYPE_AUTONA;	break;
	    case EKG_STATUS_XA:		mtype = MTYPE_AUTOBUSY;	break;
	    case EKG_STATUS_DND:	mtype = MTYPE_AUTODND;	break;
	    case EKG_STATUS_FFC:	mtype = MTYPE_AUTOFFC;	break;
	    default: return;
	}

	pkt = string_init(NULL);
	icq_pack_append(pkt, "II", cookie1, cookie2);
	icq_pack_append(pkt, "W", (uint32_t) 2);
	icq_pack_append(pkt, "s", uin);

	tlv5 = string_init(NULL);
	icq_pack_append(tlv5, "W", (uint32_t) 0);
	icq_pack_append(tlv5, "II", cookie1, cookie2);
	icq_pack_append_cap(tlv5, CAP_SRV_RELAY);
	icq_pack_append(tlv5, "tW", icq_pack_tlv_word(0xA, 1));
	icq_pack_append(tlv5, "T", icq_pack_tlv(0x0F, NULL, 0));


	rdv = string_init(NULL);
	icq_pack_append_rendezvous(rdv, 9, cookie, mtype, MFLAG_AUTO, 1, 1);
	icq_pack_append_nullterm_msg(rdv, "");
	icq_pack_append(tlv5, "T", icq_pack_tlv(0x2711, rdv->str, rdv->len));
	string_free(rdv, 1);

	icq_pack_append(pkt, "T", icq_pack_tlv(0x05, tlv5->str, tlv5->len));
	string_free(tlv5, 1);

	icq_pack_append(pkt, "T", icq_pack_tlv(0x03, NULL, 0));

	icq_makesnac(s, pkt, 0x04, 0x06, 0, 0);
	icq_send_pkt(s, pkt);
}
