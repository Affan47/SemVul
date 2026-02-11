cache_sim_write_similarity(SecureSaveInfo *ssi, CacheData *cd)
{
	guint x, y;
	guint8 buf[3 * 32];

	if (!cd || !cd->similarity || !cd->sim || !cd->sim->filled) return FALSE;

	secure_fprintf(ssi, "SimilarityGrid[32 x 32]=");
	for (y = 0; y < 32; y++)
		{
		guint s = y * 32;
		guint8 *avg_r = &cd->sim->avg_r[s];
		guint8 *avg_g = &cd->sim->avg_g[s];
		guint8 *avg_b = &cd->sim->avg_b[s];
		guint n = 0;

		for (x = 0; x < 32; x++)
			{
			buf[n++] = avg_r[x];
			buf[n++] = avg_g[x];
			buf[n++] = avg_b[x];
			}

		secure_fwrite(buf, sizeof(buf), 1, ssi);
		}

	secure_fputc(ssi, '\n');

	return TRUE;
}
