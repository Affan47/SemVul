rbd_obj_request_create(const char *object_name,
						u64 offset, u64 length,
						enum obj_request_type type)
{
	struct rbd_obj_request *obj_request;
	size_t size;
	char *name;

	rbd_assert(obj_request_type_valid(type));

	size = strlen(object_name) + 1;
	name = kmalloc(size, GFP_NOIO);
	if (!name)
		return NULL;

	obj_request = kmem_cache_zalloc(rbd_obj_request_cache, GFP_NOIO);
	if (!obj_request) {
		kfree(name);
		return NULL;
	}

	obj_request->object_name = memcpy(name, object_name, size);
	obj_request->offset = offset;
	obj_request->length = length;
	obj_request->flags = 0;
	obj_request->which = BAD_WHICH;
	obj_request->type = type;
	INIT_LIST_HEAD(&obj_request->links);
	init_completion(&obj_request->completion);
	kref_init(&obj_request->kref);

	dout("%s: \"%s\" %llu/%llu %d -> obj %p\n", __func__, object_name,
		offset, length, (int)type, obj_request);

	return obj_request;
}
