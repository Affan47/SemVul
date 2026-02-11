talloc_unlink(const void *context, void *ptr)
{
	struct talloc_chunk *tc_p, *new_p;
	void *new_parent;

	if (ptr == NULL) {
		return -1;
	}

	if (context == NULL) {
		context = null_context;
	}

	lock(context);
	if (talloc_unreference(context, ptr) == 0) {
		unlock();
		return 0;
	}

	if (context == NULL) {
		if (talloc_parent_chunk(ptr) != NULL) {
			unlock();
			return -1;
		}
	} else {
		if (talloc_chunk_from_ptr(context) != talloc_parent_chunk(ptr)) {
			unlock();
			return -1;
		}
	}

	tc_p = talloc_chunk_from_ptr(ptr);

	if (tc_p->refs == NULL) {
		int ret = _talloc_free(ptr);
		unlock();
		return ret;
	}

	new_p = talloc_parent_chunk(tc_p->refs);
	if (new_p) {
		new_parent = TC_PTR_FROM_CHUNK(new_p);
	} else {
		new_parent = NULL;
	}

	if (talloc_unreference(new_parent, ptr) != 0) {
		unlock();
		return -1;
	}

	__talloc_steal(new_parent, ptr);
	unlock();

	return 0;
}
