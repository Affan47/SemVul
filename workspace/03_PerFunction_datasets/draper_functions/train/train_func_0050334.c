normalize_div_expression(__isl_keep isl_basic_map *bmap, int div)
{
	unsigned total = isl_basic_map_total_dim(bmap);
	isl_ctx *ctx = bmap->ctx;

	if (isl_int_is_zero(bmap->div[div][0]))
		return;
	isl_seq_gcd(bmap->div[div] + 2, total, &ctx->normalize_gcd);
	isl_int_gcd(ctx->normalize_gcd, ctx->normalize_gcd, bmap->div[div][0]);
	if (isl_int_is_one(ctx->normalize_gcd))
		return;
	isl_int_fdiv_q(bmap->div[div][1], bmap->div[div][1],
			ctx->normalize_gcd);
	isl_int_divexact(bmap->div[div][0], bmap->div[div][0],
			ctx->normalize_gcd);
	isl_seq_scale_down(bmap->div[div] + 2, bmap->div[div] + 2,
			ctx->normalize_gcd, total);
}
