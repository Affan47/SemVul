radeon_renderbuffer_map(struct gl_context *ctx, struct gl_renderbuffer *rb)
{
	struct radeon_renderbuffer *rrb = radeon_renderbuffer(rb);
	GLubyte *map;
	int stride;

	if (!rb || !rrb)
		return;

	ctx->Driver.MapRenderbuffer(ctx, rb, 0, 0, rb->Width, rb->Height,
				    GL_MAP_READ_BIT | GL_MAP_WRITE_BIT,
				    &map, &stride);

	rrb->base.Map = map;
	rrb->base.RowStride = stride;

	rrb->base.ColorType = GL_UNSIGNED_BYTE;
}
