get_minibuf()
{
	if (AskBuffer) {
		register Buffer	*b;

		for (b = world; b != NULL; b = b->b_next)
			if (b == AskBuffer)
				return b;
	}
	AskBuffer = do_select((Window *)NULL, "*minibuf*");
	AskBuffer->b_type = B_SCRATCH;
	return AskBuffer;
}
