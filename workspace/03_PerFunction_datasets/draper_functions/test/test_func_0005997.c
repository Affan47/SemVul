main (int   argc,
          char *argv[])
{
	gboolean have_unowned;
	gboolean have_unowned_group;

	g_test_init (&argc, &argv, NULL);
	gtk_init (&argc, &argv);

	g_printf ("\n***\n");
	have_unowned = check_unowned_directory ();
	have_unowned_group = check_unowned_group ();
	g_printf ("***\n\n");

	g_test_add_func ("/document-saver/local", test_local);
	g_test_add_func ("/document-saver/local-new-line", test_local_newline);

	if (have_unowned)
	{
		g_test_add_func ("/document-saver/local-unowned-directory", test_local_unowned_directory);
	}

	g_test_add_func ("/document-saver/remote", test_remote);
	g_test_add_func ("/document-saver/remote-new-line", test_remote_newline);


	if (have_unowned)
	{
		g_test_add_func ("/document-saver/remote-unowned-directory", test_remote_unowned_directory);
	}

	if (have_unowned_group)
	{


	}

#ifndef G_OS_WIN32
	g_test_add_func ("/document-saver/local-permissions", test_local_permissions);

	if (have_unowned_group)
	{
		g_test_add_func ("/document-saver/local-unowned-group", test_local_unowned_group);
	}

	g_test_add_func ("/document-saver/remote-permissions", test_remote_permissions);
#endif

	return g_test_run ();
}
