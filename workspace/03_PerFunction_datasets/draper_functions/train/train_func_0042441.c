restart_conflicting_writes(struct drbd_device *device,
				       sector_t sector, int size)
{
	struct drbd_interval *i;
	struct drbd_request *req;

	drbd_for_each_overlap(i, &device->write_requests, sector, size) {
		if (!i->local)
			continue;
		req = container_of(i, struct drbd_request, i);
		if (req->rq_state & RQ_LOCAL_PENDING ||
		    !(req->rq_state & RQ_POSTPONED))
			continue;


		__req_mod(req, CONFLICT_RESOLVED, NULL);
	}
}
