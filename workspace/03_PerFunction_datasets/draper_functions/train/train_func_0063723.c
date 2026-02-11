_execute_list (AuServer *aud, int argc, char **argv)
{
    static NameTable settab[] = {
	{ "device",	_execute_list_device },
    };

    if (argc < 2) {
	fprintf (stderr, "%s:  no list operation\n", ProgramName);
	return 1;
    }

    return _do_parse (aud, argc, argv, "list", settab, NELEMS(settab), NULL);
}
