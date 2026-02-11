osd_req_add_set_attr_list(struct osd_request *or,
	const struct osd_attr *oa, unsigned nelem)
{
	unsigned total_bytes = or->set_attr.total_bytes;
	void *attr_last;
	int ret;

	if (or->attributes_mode &&
	    or->attributes_mode != OSD_CDB_GET_SET_ATTR_LISTS) {
		WARN_ON(1);
		return -EINVAL;
	}
	or->attributes_mode = OSD_CDB_GET_SET_ATTR_LISTS;

	if (!total_bytes) {
		total_bytes = _osd_req_sizeof_alist_header(or);
		ret = _alloc_set_attr_list(or, oa, nelem, total_bytes);
		if (ret)
			return ret;
		_osd_req_set_alist_type(or, or->set_attr.buff,
					OSD_ATTR_LIST_SET_RETRIEVE);
	}
	attr_last = or->set_attr.buff + total_bytes;

	for (; nelem; --nelem) {
		unsigned elem_size = _osd_req_alist_elem_size(or, oa->len);

		total_bytes += elem_size;
		if (unlikely(or->set_attr.alloc_size < total_bytes)) {
			or->set_attr.total_bytes = total_bytes - elem_size;
			ret = _alloc_set_attr_list(or, oa, nelem, total_bytes);
			if (ret)
				return ret;
			attr_last =
				or->set_attr.buff + or->set_attr.total_bytes;
		}

		_osd_req_alist_elem_encode(or, attr_last, oa);

		attr_last += elem_size;
		++oa;
	}

	or->set_attr.total_bytes = total_bytes;
	return 0;
}
