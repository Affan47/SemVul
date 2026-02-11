usage(const char *name)
{
    cerr << autosprintf(_("encfsctl version %s"), VERSION) << "\n"
	<< _("Usage:\n")


	<< autosprintf(_("%s (root dir)\n"
	"  -- displays information about the filesystem, or \n"), name);

    int offset = 0;
    while(commands[offset].name != 0)
    {
	if( commands[offset].argStr != 0 )
	{
	    cerr << "encfsctl " << commands[offset].name << " "
		<< commands[offset].argStr << "\n"
		<< gettext( commands[offset].usageStr ) << "\n";
	}
	++offset;
    }

    cerr << "\n"

	<< autosprintf(_("Example: \n%s info ~/.crypt\n"), name)
	<< "\n";
}
