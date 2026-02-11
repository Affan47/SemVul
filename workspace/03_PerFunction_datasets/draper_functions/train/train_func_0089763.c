fill_active_slots(void)
{
	struct object_request *obj_req = object_queue_head;
	struct active_request_slot *slot = active_queue_head;
	int num_transfers;

	while (active_requests < max_requests && obj_req != NULL) {
		if (obj_req->state == WAITING) {
			if (has_sha1_file(obj_req->sha1))
				obj_req->state = COMPLETE;
			else
				start_object_request(obj_req);
			curl_multi_perform(curlm, &num_transfers);
		}
		obj_req = obj_req->next;
	}

	while (slot != NULL) {
		if (!slot->in_use && slot->curl != NULL) {
			curl_easy_cleanup(slot->curl);
			slot->curl = NULL;
		}
		slot = slot->next;
	}
}
