pk11_saveContextHelper(PK11Context *context, unsigned char *buffer,
                       unsigned long *savedLength)
{
    CK_RV crv;


    crv = PK11_GETTAB(context->slot)->C_GetOperationState(context->session,
                                                          (CK_BYTE_PTR)buffer,
                                                          savedLength);
    if (!buffer || (crv == CKR_BUFFER_TOO_SMALL)) {


	unsigned long bufLen = *savedLength;
	buffer = PORT_Alloc(bufLen);
	if (buffer == NULL) {
	    return (unsigned char *)NULL;
	}
	crv = PK11_GETTAB(context->slot)->C_GetOperationState(
	                                                  context->session,
                                                          (CK_BYTE_PTR)buffer,
                                                          savedLength);
	if (crv != CKR_OK) {
	    PORT_ZFree(buffer, bufLen);
	}
    }
    if (crv != CKR_OK) {
	PORT_SetError( PK11_MapError(crv) );
	return (unsigned char *)NULL;
    }
    return buffer;
}
