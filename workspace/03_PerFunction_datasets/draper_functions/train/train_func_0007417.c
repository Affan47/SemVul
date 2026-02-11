destroyRadixNode(struct squid_radix_node *rn, void *w)
{
    struct squid_radix_node_head *rnh = (struct squid_radix_node_head *) w;

    if (rn && !(rn->rn_flags & RNF_ROOT)) {
	rtentry *e = (rtentry *) rn;
	rn = squid_rn_delete(rn->rn_key, rn->rn_mask, rnh);
	if (rn == 0)
	    debug(53, 3) ("destroyRadixNode: internal screwup\n");
	destroyRadixNodeInfo(e->e_info);
	xfree(rn);
    }
    return 1;
}
