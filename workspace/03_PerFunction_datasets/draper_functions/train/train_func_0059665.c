ole_make_bat (MSOleBAT const *metabat, size_t size_guess, guint32 block,
	      MSOleBAT *res)
{

	GArray *bat = g_array_sized_new (FALSE, FALSE,
		sizeof (guint32), size_guess);

	guint8 *used = (guint8*)g_alloca (1 + metabat->num_blocks / 8);
	memset (used, 0, 1 + metabat->num_blocks / 8);

	while (block < metabat->num_blocks) {

		if (used[block/8] & (1 << (block & 0x7)))
			break;
		used[block/8] |= 1 << (block & 0x7);

		g_array_append_val (bat, block);
		block = metabat->block [block];
	}

	res->num_blocks = bat->len;
	res->block = (guint32 *) (gpointer) g_array_free (bat, FALSE);

	if (block != BAT_MAGIC_END_OF_CHAIN) {
		g_warning ("This OLE2 file is invalid.\n"
			   "The Block Allocation Table for one of the streams had 0x%08x instead of a terminator (0x%08x).\n"
			   "We might still be able to extract some data, but you'll want to check the file.",
			   block, BAT_MAGIC_END_OF_CHAIN);
	}

	return FALSE;
}
