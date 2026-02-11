_wputstr ( WINDOW *win, const char *str, int wrap, int n ) {
	for ( ; *str && n-- ; str++ ) {
		_wputc ( win, *str, wrap );
	}
}
