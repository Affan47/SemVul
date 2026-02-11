sync_persist_startup (PRThread *tid, Sync_Cookie *cookie)
{
	SyncRequest *cur;
	int rc = 1;

	if ( SYNC_IS_INITIALIZED() && NULL != tid ) {
		SYNC_LOCK_READ();

	  	cur = sync_request_list->sync_req_head;
	  	while ( NULL != cur ) {
			if ( cur->req_tid == tid ) {
				cur->req_active = PR_TRUE;
				cur->req_cookie = cookie;
				rc = 0;
				break;
			}
			cur = cur->req_next;
		}
		SYNC_UNLOCK_READ();
	}
	return (rc);
}
