sftk_NewDBHandle(SDB *sdb, int type)
{
   SFTKDBHandle *handle = PORT_New(SFTKDBHandle);
   handle->ref = 1;
   handle->db = sdb;
   handle->update = NULL;
   handle->peerDB = NULL;
   handle->newKey = NULL;
   handle->oldKey = NULL;
   handle->updatePasswordKey = NULL;
   handle->updateID = NULL;
   handle->type = type;
   handle->passwordKey.data = NULL;
   handle->passwordKey.len = 0;
   handle->passwordLock = NULL;
   if (type == SFTK_KEYDB_TYPE) {
	handle->passwordLock = PZ_NewLock(nssILockAttribute);
   }
   sdb->app_private = handle;
   return handle;
}
