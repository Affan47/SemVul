_GetFlagsList(interp, flags, fnp)
	Tcl_Interp *interp;
	u_int32_t flags;
	const FN *fnp;
{
	Tcl_Obj *newlist, *newobj;
	int result;

	newlist = Tcl_NewObj();


	if (fnp == NULL)
		return (newlist);


	for (; fnp->mask != 0; ++fnp)
		if (LF_ISSET(fnp->mask)) {
			newobj = NewStringObj(fnp->name, strlen(fnp->name));
			result =
			    Tcl_ListObjAppendElement(interp, newlist, newobj);


			DB_ASSERT(NULL, result == TCL_OK);
		}

	return (newlist);
}
