AuthProc(char *server, char *method, char *url, char *user, char *pass,
	 char *peer)
{
    Server	  *servPtr;
    Perm          *permPtr;
    User          *userPtr;
    Tcl_HashEntry *hPtr;
    Tcl_HashSearch search;
    int status;
    char *group, buf[16];

    if (user == NULL) {
	user = "";
    }
    if (pass == NULL) {
	pass = "";
    }
    hPtr = Tcl_FindHashEntry(&serversTable, server);
    if (hPtr == NULL) {
	return NS_FORBIDDEN;
    }
    servPtr = Tcl_GetHashValue(hPtr);

    Ns_RWLockRdLock(&servPtr->lock);
    permPtr = Ns_UrlSpecificGet(server, method, url, uskey);
    if (permPtr == NULL) {
    	status = NS_OK;
	goto done;
    }


    status = NS_UNAUTHORIZED;


    hPtr = Tcl_FindHashEntry(&servPtr->users, user);
    if (hPtr == NULL) {
    	goto done;
    }
    userPtr = Tcl_GetHashValue(hPtr);
    if (userPtr->pass[0] != 0) {
    	if (pass[0] == 0) {
	    goto done;
	}
	Ns_Encrypt(pass, userPtr->pass, buf);
	if (!STREQ(userPtr->pass, buf)) {
    	    goto done;
	}
    }


    if (!ValidateUserAddr(userPtr, peer)) {


deny:
	if (*user != '\0') {
	    status = NS_FORBIDDEN;
	}
	goto done;
    }


    if (Tcl_FindHashEntry(&permPtr->denyuser, user) != NULL) {
	goto deny;
    }


    hPtr = Tcl_FirstHashEntry(&permPtr->denygroup, &search);
    while (hPtr != NULL) {
	group = Tcl_GetHashKey(&permPtr->denygroup, hPtr);
	if (Tcl_FindHashEntry(&userPtr->groups, group) != NULL) {
	    goto deny;
	}
	hPtr = Tcl_NextHashEntry(&search);
    }


    status = NS_OK;


    if (Tcl_FindHashEntry(&permPtr->allowuser, user) != NULL) {
	goto done;
    }


    hPtr = Tcl_FirstHashEntry(&permPtr->allowgroup, &search);
    while (hPtr != NULL) {
	group = Tcl_GetHashKey(&permPtr->allowgroup, hPtr);
	if (Tcl_FindHashEntry(&userPtr->groups, group) != NULL) {
	    goto done;
	}
	hPtr = Tcl_NextHashEntry(&search);
    }


    if (!permPtr->implicit_allow) {
	status = NS_UNAUTHORIZED;
    }

done:
    Ns_RWLockUnlock(&servPtr->lock);
    return status;
}
