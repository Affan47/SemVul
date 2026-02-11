group_cache_draw(GroupCache *cache, GF_TraverseState *tr_state)
{
	GF_TextureHandler *old_txh = tr_state->ctx->aspect.fill_texture;

	tr_state->ctx->aspect.fill_texture = &cache->txh;

	if (! tr_state->visual->DrawBitmap(tr_state->visual, tr_state, tr_state->ctx, NULL)) {
		visual_2d_texture_path(tr_state->visual, cache->drawable->path, tr_state->ctx, tr_state);
	}
	tr_state->ctx->aspect.fill_texture = old_txh;
}
