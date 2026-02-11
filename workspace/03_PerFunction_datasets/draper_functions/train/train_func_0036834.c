HpingChecksumCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[])
{
	Tcl_Obj *result;
	u_int16_t cksum;
	char *data;
	int len;

	result = Tcl_GetObjResult(interp);

	if (objc != 3) {
		Tcl_WrongNumArgs(interp, 2, objv, "string");
		return TCL_ERROR;
	}
	data = Tcl_GetStringFromObj(objv[2], &len);
	cksum = ars_cksum(data, len);
	Tcl_SetIntObj(result, cksum);
	return TCL_OK;
}
