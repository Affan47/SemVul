MatchStringFormat(interp, string, formatString, imageFormatPtr,
	widthPtr, heightPtr)
    Tcl_Interp *interp;
    char *string;
    char *formatString;
    Tk_PictImageFormat **imageFormatPtr;


    int *widthPtr, *heightPtr;

{
    int matched;
    Tk_PictImageFormat *formatPtr;

#ifdef DEBUG
    printf("MatchStringFormat\n");
#endif


    matched = 0;
    for (formatPtr = formatList; formatPtr != NULL;
	    formatPtr = formatPtr->nextPtr) {
	if ((formatString != NULL) && (strncasecmp(formatString,
		formatPtr->name, strlen(formatPtr->name)) != 0)) {
	    continue;
	}
	matched = 1;
	if ((formatPtr->stringMatchProc != NULL)
		&& (*formatPtr->stringMatchProc)(
                    Tcl_NewStringObj( string, -1 ),
                    Tcl_NewStringObj( formatString, -1 ),
                    widthPtr, heightPtr, interp)) {
	    break;
	}
    }

    if (formatPtr == NULL) {
	if ((formatString != NULL) && !matched) {
	    Tcl_AppendResult(interp, "image file format \"", formatString,
		    "\" is unknown", (char *) NULL);
	} else {
	    Tcl_AppendResult(interp, "no format found to parse",
		    " image data string", (char *) NULL);
	}
	return TCL_ERROR;
    }

    *imageFormatPtr = formatPtr;
    return TCL_OK;
}
