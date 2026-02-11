CKYApplet_VerifyResponse(const CKYBuffer *buf, CKYSize dataSize,
						    CKYISOStatus *apduRC) {
    CKYSize size = CKYBuffer_Size(buf);
    CKYISOStatus rc = CKYISO_INVRESPONSE;
    CKYBool valid = 0;


    if (size < 2) {
	goto done;
    }

    rc = CKYBuffer_GetShort(buf, size-2);


    if ((dataSize != CKY_SIZE_UNKNOWN) && (size != dataSize+2)) {
	goto done;
    }


    valid = (rc == CKYISO_SUCCESS) || ((rc & CKYISO_MORE_MASK) == CKYISO_MORE);

done:
    if (apduRC) {
	*apduRC = rc;
    }
    return valid;
}
