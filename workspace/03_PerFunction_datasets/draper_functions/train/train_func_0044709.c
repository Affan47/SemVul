__lookup_snap_realm(struct ceph_mds_client *mdsc,
						   u64 ino)
{
	struct rb_node *n = mdsc->snap_realms.rb_node;
	struct ceph_snap_realm *r;

	while (n) {
		r = rb_entry(n, struct ceph_snap_realm, node);
		if (ino < r->ino)
			n = n->rb_left;
		else if (ino > r->ino)
			n = n->rb_right;
		else {
			dout("lookup_snap_realm %llx %p\n", r->ino, r);
			return r;
		}
	}
	return NULL;
}
