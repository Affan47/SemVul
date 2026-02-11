test_filename_from_uri ()
{
#ifdef G_OS_WIN32
#else
	char *s;

	fileit ("file:///a", "/a");
	fileit ("file:///%41", "/A");
	fileit ("file:///home/miguel", "/home/miguel");
	fileit ("file:///home/mig%20uel", "/home/mig uel");
	ferrit ("/a");
	ferrit ("a");
	ferrit ("file://a");
	ferrit ("file:a");
	ferrit ("file:///%");
	ferrit ("file:///%0");
	ferrit ("file:///%jj");
#endif

	return OK;
}
