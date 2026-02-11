cmd_unpack_objects(int argc, const char **argv, const char *prefix)
{
	int i;
	unsigned char sha1[20];

	git_config(git_default_config);

	quiet = !isatty(2);

	for (i = 1 ; i < argc; i++) {
		const char *arg = argv[i];

		if (*arg == '-') {
			if (!strcmp(arg, "-n")) {
				dry_run = 1;
				continue;
			}
			if (!strcmp(arg, "-q")) {
				quiet = 1;
				continue;
			}
			if (!strcmp(arg, "-r")) {
				recover = 1;
				continue;
			}
			if (!strcmp(arg, "--strict")) {
				strict = 1;
				continue;
			}
			if (!prefixcmp(arg, "--pack_header=")) {
				struct pack_header *hdr;
				char *c;

				hdr = (struct pack_header *)buffer;
				hdr->hdr_signature = htonl(PACK_SIGNATURE);
				hdr->hdr_version = htonl(strtoul(arg + 14, &c, 10));
				if (*c != ',')
					die("bad %s", arg);
				hdr->hdr_entries = htonl(strtoul(c + 1, &c, 10));
				if (*c)
					die("bad %s", arg);
				len = sizeof(*hdr);
				continue;
			}
			usage(unpack_usage);
		}


		usage(unpack_usage);
	}
	SHA1_Init(&ctx);
	unpack_all();
	SHA1_Update(&ctx, buffer, offset);
	SHA1_Final(sha1, &ctx);
	if (strict)
		write_rest();
	if (hashcmp(fill(20), sha1))
		die("final sha1 did not match");
	use(20);


	while (len) {
		int ret = xwrite(1, buffer + offset, len);
		if (ret <= 0)
			break;
		len -= ret;
		offset += ret;
	}


	return has_errors;
}
