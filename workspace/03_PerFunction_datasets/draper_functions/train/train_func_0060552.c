extract_attr_from_req(struct osd_request *or, struct osd_attr *attr)
{
	struct osd_attr cur_attr = {.attr_page = 0};
	void *iter = NULL;
	int nelem;

	do {
		nelem = 1;
		osd_req_decode_get_attr_list(or, &cur_attr, &nelem, &iter);
		if ((cur_attr.attr_page == attr->attr_page) &&
		    (cur_attr.attr_id == attr->attr_id)) {
			attr->len = cur_attr.len;
			attr->val_ptr = cur_attr.val_ptr;
			return 0;
		}
	} while (iter);

	return -EIO;
}
