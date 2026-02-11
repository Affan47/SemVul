HpingGetFieldCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[])
{
	char *layer, *field, *value, *packet;
	int skip = 0;
	Tcl_Obj *result;

	if (objc != 5 && objc != 6) {
		Tcl_WrongNumArgs(interp, 2, objv, "layer field ?skip? packet");
		return TCL_ERROR;
	}
	result = Tcl_GetObjResult(interp);
	layer = Tcl_GetStringFromObj(objv[2], NULL);
	field = Tcl_GetStringFromObj(objv[3], NULL);
	if (objc == 6) {
		Tcl_GetIntFromObj(interp, objv[4], &skip);
		packet = Tcl_GetStringFromObj(objv[5], NULL);
	} else {
		packet = Tcl_GetStringFromObj(objv[4], NULL);
	}
	value = ars_d_field_get(packet, layer, field, skip);
	if (value) {
		Tcl_SetStringObj(result, value, -1);
		free(value);
	}
	return TCL_OK;
}
