gc_collect_roots(TSRMLS_D)
{
	gc_root_buffer *current = GC_G(roots).next;

	while (current != &GC_G(roots)) {
		if (current->handle && EG(objects_store).object_buckets) {
			struct _store_object *obj = &EG(objects_store).object_buckets[current->handle].bucket.obj;
			zval z;

			GC_SET_ADDRESS(obj->buffered, NULL);
			INIT_PZVAL(&z);
			Z_OBJ_HANDLE(z) = current->handle;
			Z_OBJ_HT(z) = current->u.handlers;
			zobj_collect_white(&z TSRMLS_CC);
		} else {
			GC_ZVAL_SET_ADDRESS(current->u.pz, NULL);
			zval_collect_white(current->u.pz TSRMLS_CC);
		}

		GC_REMOVE_FROM_BUFFER(current);
		current = current->next;
	}
}
