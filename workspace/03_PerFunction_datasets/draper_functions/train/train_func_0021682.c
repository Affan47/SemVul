gfire_buddy_proto_create_send_im(const guint8 *p_sid, guint32 p_imindex, const gchar *p_msg)
{
	if(!p_sid || !p_msg)
		return 0;

	guint32 offset = XFIRE_HEADER_LEN;

	guint32	msgtype = GUINT32_TO_LE(0);
	p_imindex = GUINT32_TO_LE(p_imindex);

	offset = gfire_proto_write_attr_ss("sid", 0x03, p_sid, XFIRE_SID_LEN, offset);
	offset = gfire_proto_write_attr_ss("peermsg", 0x05, NULL, 3, offset);
	offset = gfire_proto_write_attr_ss("msgtype", 0x02, &msgtype, sizeof(msgtype), offset);
	offset = gfire_proto_write_attr_ss("imindex", 0x02, &p_imindex, sizeof(p_imindex), offset);
	offset = gfire_proto_write_attr_ss("im", 0x01, p_msg, strlen(p_msg), offset);

	gfire_proto_write_header(offset, 0x02, 2, 0);

	return offset;
}
