cmd_showcruft( int argc, char **argv )
{
    (void)argc;

    RootPtr rootInfo = initRootInfo(argv[1]);

    if(!rootInfo)
	return EXIT_FAILURE;

    int filesFound = showcruft( rootInfo, "/" );

    cerr << autosprintf(
	    ngettext("Found %i invalid file.", "Found %i invalid files.",
		filesFound), filesFound) << "\n";

    return EXIT_SUCCESS;
}
