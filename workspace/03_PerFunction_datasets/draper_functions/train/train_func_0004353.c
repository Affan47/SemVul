HpingSendRawCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[])
{
	int error;
	Tcl_Obj *result;
	struct sockaddr_in sa;
	char *pkt;
	int pktlen;
	struct ars_iphdr *ip;

	if (objc != 3) {
		Tcl_WrongNumArgs(interp, 2, objv, "data");
		return TCL_ERROR;
	}
	result = Tcl_GetObjResult(interp);

	pkt = Tcl_GetStringFromObj(objv[2], &pktlen);

	if (pktlen < sizeof(struct ars_iphdr)) {
		Tcl_SetStringObj(result, "Packet shorter than IPv4 header", -1);
		return TCL_ERROR;
	}
	ip = (struct ars_iphdr*) pkt;

	sa.sin_family = AF_INET;
	memcpy(&sa.sin_addr.s_addr, &ip->daddr, 4);

	if (rawsocket == -1) {
		rawsocket = ars_open_rawsocket(NULL);
		if (rawsocket == -ARS_ERROR) {
			Tcl_SetStringObj(result, "Error opening raw socket: ", -1);
			Tcl_AppendStringsToObj(result, strerror(errno), NULL);
			return TCL_ERROR;
		}
	}

	error = sendto(rawsocket, pkt, pktlen, 0, (struct sockaddr*)&sa, sizeof(sa));
	if (error == -1) {
		Tcl_SetStringObj(result, "sendto(2): ", -1);
		Tcl_AppendStringsToObj(result, strerror(errno), NULL);
		return TCL_ERROR;
	}
	return TCL_OK;
}
