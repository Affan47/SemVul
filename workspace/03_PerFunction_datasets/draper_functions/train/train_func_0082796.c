machdep(what)
Int what; {
    switch (what) {
	case MARK    :
#if FLOATS_SUPPORTED
#if BREAK_FLOATS
		       mark(bfTemp);
#endif
		       mark(bdTemp);
#endif
		       break;
	case INSTALL : installHandlers();
		       break;
	case RESET   :
#if FLOATS_SUPPORTED
#if BREAK_FLOATS
		       bfTemp = NIL;
#endif
		       bdTemp = NIL;
#endif
	case BREAK   :
	case EXIT    : normalTerminal();
#if HUGS_FOR_WINDOWS
		       if (what==EXIT)
			   WinHugsExit();
		       else
			   SetCursor(LoadCursor(NULL,IDC_ARROW));
#endif
		       break;
    }
}
