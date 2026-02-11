__scan_for_color(
	char *name, char type, string_context_t *context)
{
	if (type != '^' || SCTX_GET_MR(*context) == NULL)
	{
		abort();
	}

	if (MR_HAS_SIDECOLOR(SCTX_GET_MR(*context)))
	{
		return False;
	}

	MR_SIDECOLOR(SCTX_GET_MR(*context)) = GetColor(name);
	MR_HAS_SIDECOLOR(SCTX_GET_MR(*context)) = True;

	return True;
}
