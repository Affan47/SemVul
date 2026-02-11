DumpString(Tcl_DString *dsPtr)
{
    char **largv;
    int i, largc;

    if (Tcl_SplitList(NULL, dsPtr->string, &largc, (CONST char***)&largv) == TCL_OK) {
	for (i = 0; i < largc; ++i) {
	    printf("\t%s\n", largv[i]);
	}
	ckfree((char *) largv);
    }
    Tcl_DStringTrunc(dsPtr, 0);
}
