insert_request_after(struct DIS_REQ *req, struct DIS_REQ *curr ) {
	if (! curr ) {
		req->next = dis_requests;
		dis_requests = req;
	} else {
		req->next = curr->next;
		curr->next = req;
	}
	return(1);
}
