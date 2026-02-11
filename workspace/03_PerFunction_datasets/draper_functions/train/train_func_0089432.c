Siren_NewCodec (Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[], SirenCodecType type) {

	SirenCodecObject *new_codec;
	char name[15];
	char * req_name = NULL;
	int sample_rate = 16000;
	char *prefix;
	Tcl_HashEntry *hPtr = NULL;
	int newHash;
	static char encoder_prefix[] = "encoder";
	static char decoder_prefix[] = "decoder";


	if( objc > 3) {
		Tcl_WrongNumArgs(interp, 1, objv, "?sample_rate? ?name?");
		Tcl_AppendResult (interp, " where the sample_rate MUST be 16000 to be compatible with MSN Messenger", (char *) NULL);
		return TCL_ERROR;
	}


	if (objc > 1) {
		if (Tcl_GetIntFromObj(interp, objv[1], &sample_rate) != TCL_OK) {
			Tcl_ResetResult(interp);
			sample_rate = 16000;
		}
	} else {
		sample_rate = 16000;
	}

	new_codec = (SirenCodecObject *) malloc(sizeof(SirenCodecObject));
	new_codec->decoder = NULL;
	new_codec->encoder = NULL;
	new_codec->codecType = type;

	if ( type == SIREN_ENCODER) {
		prefix = encoder_prefix;
	} else if (type == SIREN_DECODER) {
		prefix = decoder_prefix;
	}

	if ( objc == 3) {

	  req_name = Tcl_GetStringFromObj(objv[2], NULL);
	  if (Tcl_FindHashEntry(Coders, req_name) == NULL) {
	    strcpy(name, req_name);
	  }else {
	    sprintf(name, "%s%d", prefix, ++codec_counter);
	  }
	} else {
	  sprintf(name, "%s%d", prefix, ++codec_counter);
	}

	strcpy(new_codec->name, name);


	if ( type == SIREN_ENCODER) {
		new_codec->encoder = Siren7_NewEncoder(sample_rate);
	} else if (type == SIREN_DECODER) {
		new_codec->decoder = Siren7_NewDecoder(sample_rate);
	}

	hPtr = Tcl_CreateHashEntry(Coders, name, &newHash);
	Tcl_SetHashValue(hPtr, (ClientData) new_codec);

	Tcl_ResetResult(interp);
	Tcl_AppendResult(interp, name, NULL);

	return TCL_OK;

}
