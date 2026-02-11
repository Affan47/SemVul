s5p_mfc_enc_calc_src_size_v5(struct s5p_mfc_ctx *ctx)
{
	if (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12M) {
		ctx->buf_width = ALIGN(ctx->img_width, S5P_FIMV_NV12M_HALIGN);

		ctx->luma_size = ALIGN(ctx->img_width, S5P_FIMV_NV12M_HALIGN)
			* ALIGN(ctx->img_height, S5P_FIMV_NV12M_LVALIGN);
		ctx->chroma_size = ALIGN(ctx->img_width, S5P_FIMV_NV12M_HALIGN)
			* ALIGN((ctx->img_height >> 1), S5P_FIMV_NV12M_CVALIGN);

		ctx->luma_size = ALIGN(ctx->luma_size, S5P_FIMV_NV12M_SALIGN);
		ctx->chroma_size =
			ALIGN(ctx->chroma_size, S5P_FIMV_NV12M_SALIGN);
	} else if (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12MT) {
		ctx->buf_width = ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN);

		ctx->luma_size = ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN)
			* ALIGN(ctx->img_height, S5P_FIMV_NV12MT_VALIGN);
		ctx->chroma_size =
			ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN)
			* ALIGN((ctx->img_height >> 1), S5P_FIMV_NV12MT_VALIGN);

		ctx->luma_size = ALIGN(ctx->luma_size, S5P_FIMV_NV12MT_SALIGN);
		ctx->chroma_size =
			ALIGN(ctx->chroma_size, S5P_FIMV_NV12MT_SALIGN);
	}
}
