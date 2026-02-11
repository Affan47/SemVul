got_chunk (SoupMessage *msg, SoupBuffer *chunk, gpointer user_data)
{
	GetTestData *gtd = user_data;

	debug_printf (2, "  got chunk, %d bytes\n",
		      (int)chunk->length);
	if (chunk != gtd->current_chunk) {
		debug_printf (1, "chunk mismatch! %p vs %p\n",
			      chunk, gtd->current_chunk);
	}

	g_checksum_update (gtd->check, (guchar *)chunk->data, chunk->length);
	gtd->length += chunk->length;
}
