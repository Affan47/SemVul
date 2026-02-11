radeon_check_query_active(struct gl_context *ctx, struct radeon_state_atom *atom)
{
	radeonContextPtr radeon = RADEON_CONTEXT(ctx);
	struct radeon_query_object *query = radeon->query.current;

	if (!query || query->emitted_begin)
		return 0;
	return atom->cmd_size;
}
