cob_read_mat1_bin(G3DStream *stream, guint32 len, gboolean is_be,
	G3DObject *object)
{
	G3DMaterial *material;
	guint32 matidx;

	g_return_val_if_fail(object != NULL, FALSE);

	matidx = cob_read_e(stream, int16, is_be);
	len -= 2;

	material = g_slist_nth_data(object->materials, matidx);

	if(material)
	{
		g_free(material->name);
		material->name = g_strdup_printf("material #%d", matidx);


		g3d_stream_read_int8(stream);
		len --;


		g3d_stream_read_int8(stream);
		len --;


		g3d_stream_read_int8(stream);
		len --;


		material->r = cob_read_e(stream, float, is_be);
		material->g = cob_read_e(stream, float, is_be);
		material->b = cob_read_e(stream, float, is_be);
		material->a = cob_read_e(stream, float, is_be);
		len -= 16;
	}
	else
	{
#if DEBUG > 0
		g_debug("COB: Mat1: material #%d not used, ignoring...", matidx);
#endif
	}

    if(len > 0)
		g3d_stream_skip(stream, len);

	return TRUE;
}
