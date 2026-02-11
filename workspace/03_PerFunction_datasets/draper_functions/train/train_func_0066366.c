cob_read_file_bin(G3DStream *stream, G3DModel *model,
	gboolean is_be, G3DContext *context)
{
	G3DObject *object = NULL;
	guint32 type, id, parent_id, len;
	guint16 ver_min, ver_maj;
	gboolean exit = FALSE;

	do {
		cob_read_chunk_header_bin(stream, is_be, &type, &ver_maj, &ver_min,
			&id, &parent_id, &len);

#if DEBUG > 0
		g_debug("\\[%c%c%c%c] 0x%08x (0x%08x) %d bytes",
			(type >> 24) & 0xFF, (type >> 16) & 0xFF,
			(type >> 8) & 0xFF, type & 0xFF,
			id, parent_id, len);
#endif

		switch(type)
		{
			case G3D_IFF_MKID('E', 'N', 'D', ' '):

				exit = TRUE;
				break;

			case G3D_IFF_MKID('G', 'r', 'o', 'u'):

				object = cob_read_grou_bin(stream, len, is_be);
#if 0
				model->objects = g_slist_append(model->objects, object);
#endif
				break;

			case G3D_IFF_MKID('M', 'a', 't', '1'):
				cob_read_mat1_bin(stream, len, is_be, object);
				break;

			case G3D_IFF_MKID('P', 'o', 'l', 'H'):

				object = cob_read_polh_bin(stream, len, is_be, context);
				model->objects = g_slist_append(model->objects, object);
				break;

			case G3D_IFF_MKID('U', 'n', 'i', 't'):
				cob_read_unit_bin(stream, len, is_be);
				break;

			default:
#if DEBUG > 0
				g_warning("COB: unknown chunk type: %c%c%c%c: 0x%08x (0x%08x),"
					" %u bytes",
					(type >> 24) & 0xFF, (type >> 16) & 0xFF,
					(type >> 8) & 0xFF, type & 0xFF,
					id, parent_id, len);
#endif
				g3d_stream_skip(stream, len);
				break;
		}
	}
	while(type && !exit);

	return TRUE;
}
