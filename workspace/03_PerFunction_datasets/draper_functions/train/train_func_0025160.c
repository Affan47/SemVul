tclGdStyleCmd(Tcl_Interp * interp, GdData * gdData,
	      int argc, Tcl_Obj * CONST objv[])
{
    gdImagePtr im;
    int ncolor, *colors = NULL, i;
    Tcl_Obj **colorObjv = (Tcl_Obj **) (&objv[3]);
    int retval = TCL_OK;


    im = *(gdImagePtr *) tclhandleXlate(gdData->handleTbl,
					Tcl_GetString(objv[2]));


    ncolor = argc - 3;

    if (ncolor == 1)
	if (Tcl_ListObjGetElements(interp, objv[3],
				   &ncolor, &colorObjv) != TCL_OK)
	    return TCL_ERROR;

    colors = (int *) Tcl_Alloc(ncolor * sizeof(int));
    if (colors == NULL) {
	Tcl_SetResult(interp, "Memory allocation failed", TCL_STATIC);
	retval = TCL_ERROR;
	goto out;
    }

    for (i = 0; i < ncolor; i++)
	if (Tcl_GetIntFromObj(interp, colorObjv[i], &colors[i]) != TCL_OK) {
	    retval = TCL_ERROR;
	    break;
	}


    if (retval == TCL_OK)
	gdImageSetStyle(im, colors, ncolor);

  out:

    if (colors != NULL)
	Tcl_Free((char *) colors);

    return retval;
}
