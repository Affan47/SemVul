rbd_img_request_get(struct rbd_img_request *img_request)
{
	dout("%s: img %p (was %d)\n", __func__, img_request,
	     atomic_read(&img_request->kref.refcount));
	kref_get(&img_request->kref);
}
