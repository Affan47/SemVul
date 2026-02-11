apei_exec_pre_map_gars(struct apei_exec_context *ctx)
{
	int rc, end;

	rc = apei_exec_for_each_entry(ctx, pre_map_gar_callback,
				      NULL, &end);
	if (rc) {
		struct apei_exec_context ctx_unmap;
		memcpy(&ctx_unmap, ctx, sizeof(*ctx));
		ctx_unmap.entries = end;
		apei_exec_post_unmap_gars(&ctx_unmap);
	}

	return rc;
}
