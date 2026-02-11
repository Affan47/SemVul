rbd_osd_write_callback(struct rbd_obj_request *obj_request)
{
	dout("%s: obj %p result %d %llu\n", __func__, obj_request,
		obj_request->result, obj_request->length);


	obj_request->xferred = obj_request->length;
	obj_request_done_set(obj_request);
}
