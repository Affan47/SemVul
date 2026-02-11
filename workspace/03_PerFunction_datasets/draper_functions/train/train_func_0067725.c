sax_test (char *buf, size_t len)
{
	unsigned long time;
	iksparser *prs;
	size_t bs, i;
	int err;

	bs = block_size;
	if (0 == bs) bs = len;
	sax_tag = 0;
	sax_cdata = 0;

	t_reset ();

	prs = iks_sax_new (NULL, tagHook, cdataHook);
	i = 0;
	while (i < len) {
		if (i + bs > len) bs = len - i;
		err = iks_parse (prs, buf + i, bs, 0);
		switch (err) {
			case IKS_OK:
				break;
			case IKS_NOMEM:
				exit (2);
			case IKS_BADXML:
				fprintf (stderr, "Invalid xml at byte %ld, line %ld\n",
					iks_nr_bytes (prs), iks_nr_lines (prs));
				exit (1);
			case IKS_HOOK:
				exit (1);
		}
		i += bs;
	}

	time = t_elapsed ();

	printf ("SAX: parsing took %ld milliseconds.\n", time);
	printf ("SAX: tag hook called %d, cdata hook called %d times.\n", sax_tag, sax_cdata);

	iks_parser_delete (prs);
}
