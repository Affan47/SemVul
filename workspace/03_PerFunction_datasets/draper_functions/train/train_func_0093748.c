composite2d_draw_bitmap(GF_VisualManager *visual, GF_TraverseState *tr_state, struct _drawable_context *ctx, GF_ColorKey *col_key)
{
	u8 alpha = 0xFF;
	GF_VideoSurface offscreen_dst, video_src;
	GF_Window src_wnd, dst_wnd;
	Bool use_blit, has_scale;
	CompositeTextureStack *st;

	if (visual->compositor->disable_composite_blit) return 0;

	if (!ctx->aspect.fill_texture) return 1;
	if (ctx->transform.m[0]<0) return 0;
	if (ctx->transform.m[4]<0) {
		if (!(ctx->flags & CTX_FLIPED_COORDS)) return 0;
	} else {
		if (ctx->flags & CTX_FLIPED_COORDS) return 0;
	}
	if (ctx->transform.m[1] || ctx->transform.m[3]) return 0;
#ifndef GPAC_DISABLE_VRML
	if ((ctx->flags & CTX_HAS_APPEARANCE) && ctx->appear && ((M_Appearance*)ctx->appear)->textureTransform)
		return 0;
#endif

	alpha = GF_COL_A(ctx->aspect.fill_color);

	if (!alpha) alpha = GF_COL_A(ctx->aspect.line_color);
	if (!alpha) return 1;

	st = (CompositeTextureStack *) gf_node_get_private(visual->offscreen);

	if (!compositor_texture_rectangles(visual, ctx->aspect.fill_texture, &ctx->bi->clip, &ctx->bi->unclip, &src_wnd, &dst_wnd, &use_blit, &has_scale)) return 1;

	video_src.height = ctx->aspect.fill_texture->height;
	video_src.width = ctx->aspect.fill_texture->width;
	video_src.pitch_x = 0;
	video_src.pitch_y = ctx->aspect.fill_texture->stride;
	video_src.pixel_format = ctx->aspect.fill_texture->pixelformat;
#ifdef GF_SR_USE_DEPTH
	if (ctx->aspect.fill_texture->pixelformat==GF_PIXEL_YUVD) video_src.pixel_format = GF_PIXEL_YV12;
#endif
	video_src.video_buffer = ctx->aspect.fill_texture->data;

	memset(&offscreen_dst, 0, sizeof(GF_VideoSurface));
	offscreen_dst.width = st->txh.width;
	offscreen_dst.height = st->txh.height;
	offscreen_dst.pitch_y = st->txh.stride;
	offscreen_dst.pixel_format = st->txh.pixelformat;
	offscreen_dst.video_buffer = st->txh.data;

	gf_stretch_bits(&offscreen_dst, &video_src, &dst_wnd, &src_wnd, alpha, 0, col_key, ctx->col_mat);
	return 1;
}
