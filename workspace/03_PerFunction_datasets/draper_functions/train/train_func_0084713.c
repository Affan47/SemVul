CKYCardConnection_Destroy(CKYCardConnection *conn)
{
    if (conn == NULL) {
	return CKYSUCCESS;
    }
    if (conn->inTransaction) {
	CKYCardConnection_EndTransaction(conn);
    }
    CKYCardConnection_Disconnect(conn);
    free(conn);
    return CKYSUCCESS;
}
