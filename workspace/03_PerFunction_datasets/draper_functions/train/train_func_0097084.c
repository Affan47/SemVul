parse_file_blocks (int file, BlockFunc block_func, GkmSecret *login, gpointer user_data)
{
	gchar header[FILE_HEADER_LEN];
	GkmDataResult res;
	EggBuffer buffer;
	guint32 block;
	guint32 length;
	gsize offset;

	g_assert (file != -1);
	g_assert (block_func);


	if (!read_all_bytes (file, (guchar*)header, FILE_HEADER_LEN))
		return TRUE;


	if (memcmp (header, FILE_HEADER, FILE_HEADER_LEN) != 0) {
		g_message ("invalid header in store file");
		return FALSE;
	}

	egg_buffer_init_full (&buffer, 1024, (EggBufferAllocator)g_realloc);

	res = GKM_DATA_SUCCESS;
	for (;;) {

		egg_buffer_reset (&buffer);
		egg_buffer_resize (&buffer, 8);
		offset = 0;


		if (!read_all_bytes (file, buffer.buf, 8)) {
			res = GKM_DATA_SUCCESS;
			break;
		}


		if (!egg_buffer_get_uint32 (&buffer, offset, &offset, &length) ||
		    !egg_buffer_get_uint32 (&buffer, offset, &offset, &block) ||
		    length < 8) {
			res = GKM_DATA_FAILURE;
			g_message ("invalid block size or length in store file");
			break;
		}


		egg_buffer_resize (&buffer, length - 8);
		if (!read_all_bytes (file, buffer.buf, length - 8)) {
			res = GKM_DATA_FAILURE;
			break;
		}

		res = (block_func) (block, &buffer, login, user_data);
		if (res != GKM_DATA_SUCCESS)
			break;
	}

	egg_buffer_uninit (&buffer);
	return res;
}
