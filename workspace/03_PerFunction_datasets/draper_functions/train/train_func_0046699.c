_SetListRecnoElem(interp, list, elem1, elem2, e2size)
	Tcl_Interp *interp;
	Tcl_Obj *list;
	db_recno_t elem1;
	u_char *elem2;
	u_int32_t e2size;
{
	Tcl_Obj *myobjv[2], *thislist;
	int myobjc;

	myobjc = 2;
	myobjv[0] = Tcl_NewWideIntObj((Tcl_WideInt)elem1);
	myobjv[1] = Tcl_NewByteArrayObj(elem2, (int)e2size);
	thislist = Tcl_NewListObj(myobjc, myobjv);
	if (thislist == NULL)
		return (TCL_ERROR);
	return (Tcl_ListObjAppendElement(interp, list, thislist));

}
