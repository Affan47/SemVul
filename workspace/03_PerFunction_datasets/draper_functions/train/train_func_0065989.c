main (int argc, char *argv[])
{
	const char *datadir = "data/pgpmime";
	GMimeCryptoContext *ctx;
	struct stat st;
	char *key;
	int i;

	g_mime_init (0);

	testsuite_init (argc, argv);


	if (system ("/bin/rm -rf ./tmp") != 0)
		return EXIT_FAILURE;
	if (system ("/bin/mkdir ./tmp") != 0)
		return EXIT_FAILURE;
	setenv ("GNUPGHOME", "./tmp/.gnupg", 1);
	if (system ("/usr/bin/gpg --list-keys > /dev/null 2>&1") != 0)
		return EXIT_FAILURE;

	for (i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			datadir = argv[i];
			break;
		}
	}

	if (i < argc && (stat (datadir, &st) == -1 || !S_ISDIR (st.st_mode)))
		return 0;

	testsuite_start ("PGP/MIME implementation");

	ctx = g_mime_gpg_context_new (request_passwd, "/usr/bin/gpg");
	g_mime_gpg_context_set_always_trust ((GMimeGpgContext *) ctx, TRUE);

	testsuite_check ("GMimeGpgContext::import");
	try {
		key = g_build_filename (datadir, "gmime.gpg.pub", NULL);
		import_key (ctx, key);
		g_free (key);

		key = g_build_filename (datadir, "gmime.gpg.sec", NULL);
		import_key (ctx, key);
		g_free (key);

		testsuite_check_passed ();
	} catch (ex) {
		testsuite_check_failed ("GMimeGpgContext::import failed: %s", ex->message);
		return EXIT_FAILURE;
	} finally;

	testsuite_check ("multipart/signed");
	try {
		test_multipart_signed (ctx);
		testsuite_check_passed ();
	} catch (ex) {
		testsuite_check_failed ("multipart/signed failed: %s", ex->message);
	} finally;

	testsuite_check ("multipart/encrypted");
	try {
		test_multipart_encrypted (ctx, FALSE);
		testsuite_check_passed ();
	} catch (ex) {
		testsuite_check_failed ("multipart/encrypted failed: %s", ex->message);
	} finally;

	testsuite_check ("multipart/encrypted+sign");
	try {
		test_multipart_encrypted (ctx, TRUE);
		testsuite_check_passed ();
	} catch (ex) {
		testsuite_check_failed ("multipart/encrypted+sign failed: %s", ex->message);
	} finally;

	g_object_unref (ctx);

	testsuite_end ();

	g_mime_shutdown ();

	if (system ("/bin/rm -rf ./tmp") != 0)
		return EXIT_FAILURE;

	return testsuite_exit ();
}
