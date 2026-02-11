createTagsForArgs (cookedArgs *const args)
{
	boolean resize = FALSE;


	while (! cArgOff (args))
	{
		const char *const arg = cArgItem (args);

#ifdef MANUAL_GLOBBING
		resize |= createTagsForWildcardArg (arg);
#else
		resize |= createTagsForEntry (arg);
#endif
		cArgForth (args);
		parseOptions (args);
	}
	return resize;
}
