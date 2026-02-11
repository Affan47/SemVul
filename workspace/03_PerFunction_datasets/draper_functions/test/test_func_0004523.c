__touch_cap(struct ceph_cap *cap)
{
	struct ceph_mds_session *s = cap->session;

	spin_lock(&s->s_cap_lock);
	if (s->s_cap_iterator == NULL) {
		dout("__touch_cap %p cap %p mds%d\n", &cap->ci->vfs_inode, cap,
		     s->s_mds);
		list_move_tail(&cap->session_caps, &s->s_caps);
	} else {
		dout("__touch_cap %p cap %p mds%d NOP, iterating over caps\n",
		     &cap->ci->vfs_inode, cap, s->s_mds);
	}
	spin_unlock(&s->s_cap_lock);
}
