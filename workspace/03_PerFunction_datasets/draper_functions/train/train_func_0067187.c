gfire_chat_proto_create_change_password(const guint8 *p_cid, const gchar *p_password)
{
	guint32 offset = XFIRE_HEADER_LEN;

	if(!p_cid || !p_password)
		return 0;

	guint32 climsg = GUINT32_TO_LE(0x4D15);
	offset = gfire_proto_write_attr_ss("climsg", 0x02, &climsg, sizeof(climsg), offset);

	offset = gfire_proto_write_attr_ss("msg", 0x09, NULL, 2, offset);

	offset = gfire_proto_write_attr_bs(0x04, 0x06, p_cid, XFIRE_CHATID_LEN, offset);

	offset = gfire_proto_write_attr_bs(0x5F, 0x01, p_password, strlen(p_password), offset);

	gfire_proto_write_header(offset, 0x19, 2, 0);

	return offset;
}
