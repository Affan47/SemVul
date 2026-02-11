rbd_obj_read_sync(struct rbd_device *rbd_dev,
				const char *object_name,
				u64 offset, u64 length, void *buf)

{
	struct ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	struct rbd_obj_request *obj_request;
	struct page **pages = NULL;
	u32 page_count;
	size_t size;
	int ret;

	page_count = (u32) calc_pages_for(offset, length);
	pages = ceph_alloc_page_vector(page_count, GFP_KERNEL);
	if (IS_ERR(pages))
		return PTR_ERR(pages);

	ret = -ENOMEM;
	obj_request = rbd_obj_request_create(object_name, offset, length,
							OBJ_REQUEST_PAGES);
	if (!obj_request)
		goto out;

	obj_request->pages = pages;
	obj_request->page_count = page_count;

	obj_request->osd_req = rbd_osd_req_create(rbd_dev, OBJ_OP_READ, 1,
						  obj_request);
	if (!obj_request->osd_req)
		goto out;

	osd_req_op_extent_init(obj_request->osd_req, 0, CEPH_OSD_OP_READ,
					offset, length, 0, 0);
	osd_req_op_extent_osd_data_pages(obj_request->osd_req, 0,
					obj_request->pages,
					obj_request->length,
					obj_request->offset & ~PAGE_MASK,
					false, false);
	rbd_osd_req_format_read(obj_request);

	ret = rbd_obj_request_submit(osdc, obj_request);
	if (ret)
		goto out;
	ret = rbd_obj_request_wait(obj_request);
	if (ret)
		goto out;

	ret = obj_request->result;
	if (ret < 0)
		goto out;

	rbd_assert(obj_request->xferred <= (u64) SIZE_MAX);
	size = (size_t) obj_request->xferred;
	ceph_copy_from_page_vector(pages, buf, 0, size);
	rbd_assert(size <= (size_t)INT_MAX);
	ret = (int)size;
out:
	if (obj_request)
		rbd_obj_request_put(obj_request);
	else
		ceph_release_page_vector(pages, page_count);

	return ret;
}
