GB_EXIT()
{
	#ifndef NO_X_WINDOW
		X11_exit();
	#endif

	delete qApp;
}
