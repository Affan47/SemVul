tclGdColorCmd(Tcl_Interp * interp, GdData * gdData,
	      int argc, Tcl_Obj * CONST objv[])
{
    gdImagePtr im;
    int subi, nsub, i, args[3];

    nsub = (sizeof colorCmdVec) / (sizeof colorCmdVec[0]);
    if (argc >= 3) {

	for (subi = 0; subi < nsub; subi++) {
	    if (strcmp(colorCmdVec[subi].cmd, Tcl_GetString(objv[2])) == 0) {

		if (argc - 2 < colorCmdVec[subi].minargs ||
		    argc - 2 > colorCmdVec[subi].maxargs) {
		    Tcl_AppendResult(interp,
				     "wrong # args: should be \"gd color ",
				     colorCmdVec[subi].cmd, " ",
				     colorCmdVec[subi].usage, "\"", 0);
		    return TCL_ERROR;
		}


		im = *(gdImagePtr *) tclhandleXlate(gdData->handleTbl,
						    Tcl_GetString(objv
								  [3]));


		for (i = 0; i < argc - 4; i++) {
		    if (Tcl_GetIntFromObj(interp, objv[i + 4], &args[i]) !=
			TCL_OK) {


#if 0
			if (args[i] < 0 || args[i] > 255) {
#else

			if (args[i] < -255 || args[i] > 255) {
#endif
			    Tcl_SetResult(interp,
					  "argument out of range 0-255",
					  TCL_STATIC);
			    return TCL_ERROR;
			}
		    }
		}


		return (*colorCmdVec[subi].f) (interp, im, argc - 4, args);
	    }
	}
    }


    if (argc > 2) {
	Tcl_AppendResult(interp, "bad option \"",
			 Tcl_GetString(objv[2]), "\": ", 0);
    } else {
	Tcl_AppendResult(interp, "wrong # args: ", 0);
    }
    Tcl_AppendResult(interp, "should be ", 0);
    for (subi = 0; subi < nsub; subi++)
	Tcl_AppendResult(interp, (subi > 0 ? ", " : ""),
			 colorCmdVec[subi].cmd, 0);

    return TCL_ERROR;
}
