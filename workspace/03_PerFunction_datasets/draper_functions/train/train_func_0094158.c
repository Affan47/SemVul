prefetch(unsigned char *sha1)
{
	struct object_request *newreq;
	struct object_request *tail;
	char *filename = sha1_file_name(sha1);

	newreq = xmalloc(sizeof(*newreq));
	hashcpy(newreq->sha1, sha1);
	newreq->repo = alt;
	newreq->url = NULL;
	newreq->local = -1;
	newreq->state = WAITING;
	snprintf(newreq->filename, sizeof(newreq->filename), "%s", filename);
	snprintf(newreq->tmpfile, sizeof(newreq->tmpfile),
		 "%s.temp", filename);
	newreq->slot = NULL;
	newreq->next = NULL;

	if (object_queue_head == NULL) {
		object_queue_head = newreq;
	} else {
		tail = object_queue_head;
		while (tail->next != NULL) {
			tail = tail->next;
		}
		tail->next = newreq;
	}

#ifdef USE_CURL_MULTI
	fill_active_slots();
	step_active_slots();
#endif
}
