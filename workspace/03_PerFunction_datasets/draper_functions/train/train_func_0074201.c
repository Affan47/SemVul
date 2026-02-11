sftkdb_Commit(SFTKDBHandle *handle)
{
    CK_RV crv = CKR_OK;
    SDB *db;

    if (handle == NULL) {
	return CKR_OK;
    }
    db = SFTK_GET_SDB(handle);
    if (db) {
	(*db->sdb_Commit)(db);
    }
    return crv;
}
