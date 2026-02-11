ModBufs(allp)
bool	allp;
{
	register Buffer	*b;

	for (b = world; b != NULL; b = b->b_next)
		if (b->b_type != B_SCRATCH
		&& (b->b_type == B_FILE || allp)
		&& IsModified(b))
			return YES;
	return NO;
}
