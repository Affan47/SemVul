nbd_clear_que(struct nbd_device *nbd)
{
	struct request *req;

	BUG_ON(nbd->magic != NBD_MAGIC);


	BUG_ON(nbd->sock);
	BUG_ON(nbd->active_req);

	while (!list_empty(&nbd->queue_head)) {
		req = list_entry(nbd->queue_head.next, struct request,
				 queuelist);
		list_del_init(&req->queuelist);
		req->errors++;
		nbd_end_request(nbd, req);
	}

	while (!list_empty(&nbd->waiting_queue)) {
		req = list_entry(nbd->waiting_queue.next, struct request,
				 queuelist);
		list_del_init(&req->queuelist);
		req->errors++;
		nbd_end_request(nbd, req);
	}
	dev_dbg(disk_to_dev(nbd->disk), "queue cleared\n");
}
