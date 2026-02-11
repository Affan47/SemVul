usage(const char *program_name, bool brief)
{
	cout << "Usage: " << program_name << " NEW_CONTEXT DIR [OPTIONS] [EXPRESSION]" << endl << endl;
	if (brief)
	{
		cout << "\tTry " << program_name << " --help for more help." << endl << endl;
		return;
	}

	cout << "Replace SELinux file contexts for files matching a given context." << endl << endl;

	cout << "REQUIRED ARGUMENTS :" << endl;
	cout << "  NEW_CONTEXT                    partial or full context to relabel" << endl;
	cout << "  DIR                            starting directory to replace" << endl;
	cout << endl;
	cout << "EXPRESSION:" << endl;
	cout << "  -t TYPE,  --type=TYPE          find contexts with type TYPE" << endl;
	cout << "  -u USER,  --user=USER          find contexts with user USER" << endl;
	cout << "  -r ROLE,  --role=ROLE          find contexts with role ROLE" << endl;
	cout << "  -m RANGE, --mls-range=RANGE    find contexts with MLS range RANGE" << endl;
	cout << "  --context=CONTEXT              partial or full context to find" << endl;
	cout << "                                 (overrides expression options above)" << endl;
	cout << "  -p PATH,  --path=PATH          find files in PATH" << endl;
	cout << "  -c CLASS, --class=CLASS        find files of object class CLASS" << endl;
	cout << endl;

	cout << "OPTIONS:" << endl;
	cout << "  -R, --regex                    enable regular expressions" << endl;
	cout << "  -v, --verbose                  show context of matching files" << endl;
	cout << "  -h, --help                     print this help text and exit" << endl;
	cout << "  -V, --version                  print version information and exit" << endl;
	cout << endl;
	cout << "If the fclist does not contain MLS ranges and -m was given," << endl;
	cout << "then the search will return nothing." << endl;
	cout << endl;
	cout << "NEW_CONTEXT is as a colon separated list of user, role, type, and MLS range" << endl;
	cout << "such as follows: user_u:object_r:user_t:s0.  If a field is not specified," << endl;
	cout << "that portion of the context will not be replaced." << endl;
	cout << "Examples:" << endl;
	cout << "    replcon ::type_t: ." << endl;
	cout << "        Replace all files and subdirectories in current directory with" << endl;
	cout << "        type type_t, recursing within the directory." << endl;
	cout << "    replcon -u user_u *:role_r:* ." << endl;
	cout << "        Replace files that contain user_u with role role_r." << endl;
	cout << "    replcon --context ::type_t:so :::s0:c0 /tmp" << endl;
	cout << "        Replace files with type type_t and level s0 in /tmp with MLS" << endl;
	cout << "        range s0:c0." << endl;
}
