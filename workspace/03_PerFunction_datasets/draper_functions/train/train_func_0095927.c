cli_scandesc(int desc, cli_ctx *ctx, cli_file_t ftype, uint8_t ftonly, struct cli_matched_type **ftoffset, unsigned int acmode, struct cli_ac_result **acres)
{
    int ret = CL_EMEM, empty;
    fmap_t *map = *ctx->fmap;

    if((*ctx->fmap = fmap_check_empty(desc, 0, 0, &empty))) {
	ret = cli_fmap_scandesc(ctx, ftype, ftonly, ftoffset, acmode, acres, NULL);
	map->dont_cache_flag = (*ctx->fmap)->dont_cache_flag;
	funmap(*ctx->fmap);
    }
    *ctx->fmap = map;
    if(empty)
	return CL_CLEAN;
    return ret;
}
