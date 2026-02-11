__unregister_session(struct ceph_mds_client *mdsc,
			       struct ceph_mds_session *s)
{
	dout("__unregister_session mds%d %p\n", s->s_mds, s);
	BUG_ON(mdsc->sessions[s->s_mds] != s);
	mdsc->sessions[s->s_mds] = NULL;
	ceph_con_close(&s->s_con);
	ceph_put_mds_session(s);
	atomic_dec(&mdsc->num_sessions);
}
