read_buffer_mpi (EggBuffer *buffer,
                 gsize *offset,
                 GckBuilder *builder,
                 gulong attribute_type)
{
	const guchar *data;
	gsize len;

	if (!egg_buffer_get_byte_array (buffer, *offset, offset, &data, &len))
		return FALSE;

	gck_builder_add_data (builder, attribute_type, data, len);
	return TRUE;
}
