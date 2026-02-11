GDrawCreateDisplays(char *displayname,char *programname) {
    GIO_SetThreadCallback((void (*)(void *,void *,void *)) GDrawSyncThread);
    screen_display = _GXDraw_CreateDisplay(displayname,programname);
    printer_display = _GPSDraw_CreateDisplay();
    if ( screen_display==NULL ) {
	fprintf( stderr, "Could not open screen.\n" );
#if __Mac
	fprintf( stderr, "You must start X11 before you can start %s\n", programname);
	fprintf( stderr, " X11 is optional software found on your install DVD.\n" );
#elif __CygWin
	fprintf( stderr, "You must start X11 before you can start %s\n", programname);
	fprintf( stderr, " X11 may be obtained from the cygwin site in a separate package.\n" );
#endif
exit(1);
    }
}
