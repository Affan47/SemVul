radeonSpanRenderFinish(struct gl_context * ctx)
{
	_swrast_flush(ctx);
	_swrast_unmap_textures(ctx);

	radeon_unmap_framebuffer(ctx, ctx->DrawBuffer);
	if (ctx->ReadBuffer != ctx->DrawBuffer)
		radeon_unmap_framebuffer(ctx, ctx->ReadBuffer);
}
