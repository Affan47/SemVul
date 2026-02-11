decode_rc_list(struct xdr_stream *xdr,
			       struct referring_call_list *rc_list)
{
	__be32 *p;
	int i;
	__be32 status;

	status = decode_sessionid(xdr, &rc_list->rcl_sessionid);
	if (status)
		goto out;

	status = htonl(NFS4ERR_RESOURCE);
	p = read_buf(xdr, sizeof(uint32_t));
	if (unlikely(p == NULL))
		goto out;

	rc_list->rcl_nrefcalls = ntohl(*p++);
	if (rc_list->rcl_nrefcalls) {
		p = read_buf(xdr,
			     rc_list->rcl_nrefcalls * 2 * sizeof(uint32_t));
		if (unlikely(p == NULL))
			goto out;
		rc_list->rcl_refcalls = kmalloc_array(rc_list->rcl_nrefcalls,
						sizeof(*rc_list->rcl_refcalls),
						GFP_KERNEL);
		if (unlikely(rc_list->rcl_refcalls == NULL))
			goto out;
		for (i = 0; i < rc_list->rcl_nrefcalls; i++) {
			rc_list->rcl_refcalls[i].rc_sequenceid = ntohl(*p++);
			rc_list->rcl_refcalls[i].rc_slotid = ntohl(*p++);
		}
	}
	status = 0;

out:
	return status;
}
