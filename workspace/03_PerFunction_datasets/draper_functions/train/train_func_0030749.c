fz_evict_glyph_cache(fz_context *ctx)
{
	fz_glyph_cache *cache = ctx->glyph_cache;
	fz_glyph_key *key;
	fz_pixmap *pixmap;
	int i;

	for (i = 0; i < fz_hash_len(ctx, cache->hash); i++)
	{
		key = fz_hash_get_key(ctx, cache->hash, i);
		if (key->font)
			fz_drop_font(ctx, key->font);
		pixmap = fz_hash_get_val(ctx, cache->hash, i);
		if (pixmap)
			fz_drop_pixmap(ctx, pixmap);
	}

	cache->total = 0;

	fz_empty_hash(ctx, cache->hash);
}
