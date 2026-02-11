document (char *xml)
{
	enum ikserror err;
	iksparser *p;

	nr_tests++;
	if (my_x) iks_delete (my_x);
	p = iks_dom_new (&my_x);
	err = iks_parse (p, xml, 0, 1);
	switch (err) {
		case IKS_OK:
			break;
		case IKS_NOMEM:
			PR_TEST;
			puts ("Not enough memory.");
			exit (1);
		case IKS_BADXML:
			PR_TEST;
			printf ("Invalid xml at byte %ld in\n[%s]\n", iks_nr_bytes (p), xml);
			exit (1);
		case IKS_HOOK:
			PR_TEST;
			puts ("Hook.");
	}
	iks_parser_delete (p);
}
