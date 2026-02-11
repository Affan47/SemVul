gfire_p2p_dl_proto_send_file_chunk_info(gfire_p2p_session *p_session, guint32 p_fileid, guint64 p_offset,
										   guint32 p_size, const gchar *p_checksum, guint32 p_msgid)
{
	if(!p_session || !p_checksum)
		return 0;

	guint32 offset = GFIRE_P2P_HEADER_LEN;

	p_fileid = GUINT32_TO_LE(p_fileid);
	offset = gfire_proto_write_attr_ss("fileid", 0x02, &p_fileid, 4, offset);

	p_offset = GUINT64_TO_LE(p_offset);
	offset = gfire_proto_write_attr_ss("offset", 0x07, &p_offset, 8, offset);

	p_size = GUINT32_TO_LE(p_size);
	offset = gfire_proto_write_attr_ss("size", 0x02, &p_size, 4, offset);

	offset = gfire_proto_write_attr_ss("checksum", 0x01, p_checksum, strlen(p_checksum), offset);

	p_msgid = GUINT32_TO_LE(p_msgid);
	offset = gfire_proto_write_attr_ss("msgid", 0x02, &p_msgid, 4, offset);

	gfire_proto_write_header32(offset, 0x3E8A, 5, 0);

	guint8 *tmp_buf = g_malloc0(offset);
	gfire_network_buffout_copy(tmp_buf, offset);

#ifdef DEBUG
	purple_debug_misc("gfire", "P2P: Sending chunk info\n");
#endif
	gfire_p2p_session_send_data32_packet(p_session, tmp_buf, offset, "DL");
	g_free(tmp_buf);

	return offset;
}
