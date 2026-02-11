isl_basic_map_free(__isl_take isl_basic_map *bmap)
{
	if (!bmap)
		return NULL;

	if (--bmap->ref > 0)
		return NULL;

	isl_ctx_deref(bmap->ctx);
	free(bmap->div);
	isl_blk_free(bmap->ctx, bmap->block2);
	free(bmap->ineq);
	isl_blk_free(bmap->ctx, bmap->block);
	isl_vec_free(bmap->sample);
	isl_space_free(bmap->dim);
	free(bmap);

	return NULL;
}
