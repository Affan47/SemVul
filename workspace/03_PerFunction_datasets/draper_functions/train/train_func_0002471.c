AddGroupCmd(Server *servPtr, Tcl_Interp *interp, int argc, char *argv[])
{
    char *name, *user;
    User *userPtr;
    Group *groupPtr;
    Tcl_HashSearch search;
    Tcl_HashEntry *hPtr;
    int   new, param;

    if (argc < 4) {
	Tcl_AppendResult(interp, "wrong # args: should be \"",
			 argv[0], " ", argv[1], " name user ?user ...?",
			 NULL);
	return TCL_ERROR;
    }


    name = argv[2];
    groupPtr = ns_malloc(sizeof(Group));
    Tcl_InitHashTable(&groupPtr->users, TCL_STRING_KEYS);


    for (param = 3; param < argc; param++) {
    	user = argv[param];
    	hPtr = Tcl_FindHashEntry(&servPtr->users, user);
	if (hPtr == NULL) {
	    Tcl_AppendResult(interp, "no such user: ", user, NULL);
	    goto fail;
	}
	userPtr = Tcl_GetHashValue(hPtr);


	hPtr = Tcl_CreateHashEntry(&groupPtr->users, user, &new);
	if (!new) {
dupuser:
	    Tcl_AppendResult(interp,
	    	"user \"", user, "\" already in group \"", name, "\"", NULL);
	    goto fail;
	}
	Tcl_SetHashValue(hPtr, userPtr);


	hPtr = Tcl_CreateHashEntry(&userPtr->groups, name, &new);
	if (!new) {
	    goto dupuser;
	}
	Tcl_SetHashValue(hPtr, groupPtr);
    }


    hPtr = Tcl_CreateHashEntry(&servPtr->groups, name, &new);
    if (!new) {
	Tcl_AppendResult(interp, "duplicate group: ", name, NULL);
	goto fail;
    }
    Tcl_SetHashValue(hPtr, groupPtr);
    return TCL_OK;

fail:
    hPtr = Tcl_FirstHashEntry(&groupPtr->users, &search);
    while (hPtr != NULL) {
	userPtr = Tcl_GetHashValue(hPtr);
	hPtr = Tcl_FindHashEntry(&userPtr->groups, name);
	if (hPtr != NULL) {
	    Tcl_DeleteHashEntry(hPtr);
	}
	hPtr = Tcl_NextHashEntry(&search);
    }
    Tcl_DeleteHashTable(&groupPtr->users);
    ns_free(groupPtr);
    return TCL_ERROR;
}
