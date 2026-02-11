sync_add_request( SyncRequest *req )
{
	int rc = 0;
	if ( SYNC_IS_INITIALIZED() && NULL != req ) {
		SYNC_LOCK_WRITE();
		if (sync_request_list->sync_req_cur_persist < sync_request_list->sync_req_max_persist) {
			sync_request_list->sync_req_cur_persist++;
			req->req_next = sync_request_list->sync_req_head;
			sync_request_list->sync_req_head = req;
		} else {
			rc = 1;
		}
		SYNC_UNLOCK_WRITE();
	}
	return(rc);
}
