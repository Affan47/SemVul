skd_recover_requests(struct skd_device *skdev, int requeue)
{
	int i;

	for (i = 0; i < skdev->num_req_context; i++) {
		struct skd_request_context *skreq = &skdev->skreq_table[i];

		if (skreq->state == SKD_REQ_STATE_BUSY) {
			skd_log_skreq(skdev, skreq, "recover");

			SKD_ASSERT((skreq->id & SKD_ID_INCR) != 0);
			SKD_ASSERT(skreq->req != NULL);


			if (skreq->n_sg > 0)
				skd_postop_sg_list(skdev, skreq);

			if (requeue &&
			    (unsigned long) ++skreq->req->special <
			    SKD_MAX_RETRIES)
				blk_requeue_request(skdev->queue, skreq->req);
			else
				skd_end_request(skdev, skreq, -EIO);

			skreq->req = NULL;

			skreq->state = SKD_REQ_STATE_IDLE;
			skreq->id += SKD_ID_INCR;
		}
		if (i > 0)
			skreq[-1].next = skreq;
		skreq->next = NULL;
	}
	skdev->skreq_free_list = skdev->skreq_table;

	for (i = 0; i < skdev->num_fitmsg_context; i++) {
		struct skd_fitmsg_context *skmsg = &skdev->skmsg_table[i];

		if (skmsg->state == SKD_MSG_STATE_BUSY) {
			skd_log_skmsg(skdev, skmsg, "salvaged");
			SKD_ASSERT((skmsg->id & SKD_ID_INCR) != 0);
			skmsg->state = SKD_MSG_STATE_IDLE;
			skmsg->id += SKD_ID_INCR;
		}
		if (i > 0)
			skmsg[-1].next = skmsg;
		skmsg->next = NULL;
	}
	skdev->skmsg_free_list = skdev->skmsg_table;

	for (i = 0; i < skdev->n_special; i++) {
		struct skd_special_context *skspcl = &skdev->skspcl_table[i];


		if (skspcl->req.state == SKD_REQ_STATE_BUSY) {
			if (skspcl->orphaned) {
				pr_debug("%s:%s:%d orphaned %p\n",
					 skdev->name, __func__, __LINE__,
					 skspcl);
				skd_release_special(skdev, skspcl);
			} else {
				pr_debug("%s:%s:%d not orphaned %p\n",
					 skdev->name, __func__, __LINE__,
					 skspcl);
				skspcl->req.state = SKD_REQ_STATE_ABORTED;
			}
		}
	}
	skdev->skspcl_free_list = skdev->skspcl_table;

	for (i = 0; i < SKD_N_TIMEOUT_SLOT; i++)
		skdev->timeout_slot[i] = 0;

	skdev->in_flight = 0;
}
