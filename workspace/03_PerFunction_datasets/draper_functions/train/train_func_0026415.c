wb_liability_has_conflict (wb_inode_t *wb_inode, wb_request_t *req)
{
        wb_request_t *each     = NULL;

        list_for_each_entry (each, &wb_inode->liability, lie) {
		if (wb_requests_conflict (each, req))
			return _gf_true;
        }

        return _gf_false;
}
