_osd_req_list_objects(struct osd_request *or,
	__be16 action, const struct osd_obj_id *obj, osd_id initial_id,
	struct osd_obj_id_list *list, unsigned nelem)
{
	struct request_queue *q = osd_request_queue(or->osd_dev);
	u64 len = nelem * sizeof(osd_id) + sizeof(*list);
	struct bio *bio;

	_osd_req_encode_common(or, action, obj, (u64)initial_id, len);

	if (list->list_identifier)
		_osd_req_encode_olist(or, list);

	WARN_ON(or->in.bio);
	bio = bio_map_kern(q, list, len, or->alloc_flags);
	if (IS_ERR(bio)) {
		OSD_ERR("!!! Failed to allocate list_objects BIO\n");
		return PTR_ERR(bio);
	}

	bio->bi_rw &= ~REQ_WRITE;
	or->in.bio = bio;
	or->in.total_bytes = bio->bi_iter.bi_size;
	return 0;
}
