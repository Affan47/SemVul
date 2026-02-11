SECU_FileToItem(SECItem *dst, PRFileDesc *src)
{
    PRFileInfo info;
    PRInt32 numBytes;
    PRStatus prStatus;

    if (src == PR_STDIN)
	return secu_StdinToItem(dst);

    prStatus = PR_GetOpenFileInfo(src, &info);

    if (prStatus != PR_SUCCESS) {
	PORT_SetError(SEC_ERROR_IO);
	return SECFailure;
    }


    dst->data = 0;
    if (!SECITEM_AllocItem(NULL, dst, info.size))
	goto loser;

    numBytes = PR_Read(src, dst->data, info.size);
    if (numBytes != info.size) {
	PORT_SetError(SEC_ERROR_IO);
	goto loser;
    }

    return SECSuccess;
loser:
    SECITEM_FreeItem(dst, PR_FALSE);
    dst->data = NULL;
    return SECFailure;
}
