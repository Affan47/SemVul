mtd_blktrans_request(struct request_queue *rq)
{
	struct mtd_blktrans_dev *dev;
	struct request *req = NULL;

	dev = rq->queuedata;

	if (!dev)
		while ((req = blk_fetch_request(rq)) != NULL)
			__blk_end_request_all(req, -ENODEV);
	else
		queue_work(dev->wq, &dev->work);
}
