_osd_req_alist_elem_size(struct osd_request *or, unsigned len)
{
	return osd_req_is_ver1(or) ?
		osdv1_attr_list_elem_size(len) :
		osdv2_attr_list_elem_size(len);
}
