__get_oldest_req(struct ceph_mds_client *mdsc)
{
	if (RB_EMPTY_ROOT(&mdsc->request_tree))
		return NULL;
	return rb_entry(rb_first(&mdsc->request_tree),
			struct ceph_mds_request, r_node);
}
