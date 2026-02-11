_osd_req_is_alist_type(struct osd_request *or,
	void *list, int list_type)
{
	if (!list)
		return false;

	if (osd_req_is_ver1(or)) {
		struct osdv1_attributes_list_header *attr_list = list;

		return attr_list->type == list_type;
	} else {
		struct osdv2_attributes_list_header *attr_list = list;

		return attr_list->type == list_type;
	}
}
