__open_session(struct ceph_mds_client *mdsc,
			  struct ceph_mds_session *session)
{
	struct ceph_msg *msg;
	int mstate;
	int mds = session->s_mds;


	mstate = ceph_mdsmap_get_state(mdsc->mdsmap, mds);
	dout("open_session to mds%d (%s)\n", mds,
	     ceph_mds_state_name(mstate));
	session->s_state = CEPH_MDS_SESSION_OPENING;
	session->s_renew_requested = jiffies;


	msg = create_session_open_msg(mdsc, session->s_seq);
	if (!msg)
		return -ENOMEM;
	ceph_con_send(&session->s_con, msg);
	return 0;
}
