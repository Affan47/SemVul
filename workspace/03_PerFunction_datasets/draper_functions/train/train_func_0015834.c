XSecurityGenerateAuthorization(
    Display *dpy,
    Xauth *auth_in,
    unsigned long valuemask,
    XSecurityAuthorizationAttributes *attributes,
    XSecurityAuthorization *auth_id_return)
{
    XExtDisplayInfo *info = find_display (dpy);
    register xSecurityGenerateAuthorizationReq *req;
    xSecurityGenerateAuthorizationReply rep;
    Xauth *auth_return;
    unsigned long values[3];
    unsigned long *value = values;
    unsigned int nvalues;

    *auth_id_return = 0;


    SecurityCheckExtension (dpy, info, (Xauth *)NULL);

    LockDisplay(dpy);
    SecurityGetReq(SecurityGenerateAuthorization, req, info);

    req->nbytesAuthProto = auth_in->name_length;
    req->nbytesAuthData  = auth_in->data_length;


    req->length += (auth_in->name_length + (unsigned)3) >> 2;
    req->length += (auth_in->data_length + (unsigned)3) >> 2;


    req->valueMask = valuemask & XSecurityAllAuthorizationAttributes;
    nvalues = Ones(req->valueMask);
    req->length += nvalues;


    Data(dpy, auth_in->name, auth_in->name_length);
    Data(dpy, auth_in->data, auth_in->data_length);


    if (valuemask & XSecurityTimeout)	 *value++ = attributes->timeout;
    if (valuemask & XSecurityTrustLevel) *value++ = attributes->trust_level;
    if (valuemask & XSecurityGroup)	 *value++ = attributes->group;
    if (valuemask & XSecurityEventMask)	 *value++ = attributes->event_mask;

    nvalues <<= 2;
    Data32(dpy, (long *)values, (long)nvalues);

    if (!_XReply (dpy, (xReply *) &rep, 0, xFalse)) {
	UnlockDisplay (dpy);
	SyncHandle ();
	return (Xauth *)NULL;
    }

    *auth_id_return = rep.authId;


    if ((auth_return = (Xauth *)Xcalloc(1,
		(sizeof(Xauth) + auth_in->name_length + rep.dataLength))))
    {
	auth_return->data_length = rep.dataLength;
	auth_return->data = (char *)&auth_return[1];
	_XReadPad(dpy, auth_return->data, (long)rep.dataLength);

	auth_return->name_length = auth_in->name_length;
	auth_return->name = auth_return->data + auth_return->data_length;
	memcpy(auth_return->name, auth_in->name, auth_return->name_length);
    }
    else
    {
	_XEatDataWords(dpy, rep.length);
    }

    UnlockDisplay (dpy);
    SyncHandle ();
    return auth_return;

}
