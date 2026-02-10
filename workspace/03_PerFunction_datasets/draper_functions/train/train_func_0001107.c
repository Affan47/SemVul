__do_request(struct ceph_mds_client *mdsc,
			struct ceph_mds_request *req)
{
	struct ceph_mds_session *session = NULL;
	int mds = -1;
	int err = 0;

	if (req->r_err || req->r_got_result) {
		if (req->r_aborted)
			__unregister_request(mdsc, req);
		goto out;
	}

	if (req->r_timeout &&
	    time_after_eq(jiffies, req->r_started + req->r_timeout)) {
		dout("do_request timed out\n");
		err = -EIO;
		goto finish;
	}
	if (ACCESS_ONCE(mdsc->fsc->mount_state) == CEPH_MOUNT_SHUTDOWN) {
		dout("do_request forced umount\n");
		err = -EIO;
		goto finish;
	}

	put_request_session(req);

	mds = __choose_mds(mdsc, req);
	if (mds < 0 ||
	    ceph_mdsmap_get_state(mdsc->mdsmap, mds) < CEPH_MDS_STATE_ACTIVE) {
		dout("do_request no mds or not active, waiting for map\n");
		list_add(&req->r_wait, &mdsc->waiting_for_map);
		goto out;
	}


	session = __ceph_lookup_mds_session(mdsc, mds);
	if (!session) {
		session = register_session(mdsc, mds);
		if (IS_ERR(session)) {
			err = PTR_ERR(session);
			goto finish;
		}
	}
	req->r_session = get_session(session);

	dout("do_request mds%d session %p state %s\n", mds, session,
	     ceph_session_state_name(session->s_state));
	if (session->s_state != CEPH_MDS_SESSION_OPEN &&
	    session->s_state != CEPH_MDS_SESSION_HUNG) {
		if (session->s_state == CEPH_MDS_SESSION_NEW ||
		    session->s_state == CEPH_MDS_SESSION_CLOSING)
			__open_session(mdsc, session);
		list_add(&req->r_wait, &session->s_waiting);
		goto out_session;
	}


	req->r_resend_mds = -1;

	if (req->r_request_started == 0)
		req->r_request_started = jiffies;

	err = __prepare_send_request(mdsc, req, mds, false);
	if (!err) {
		ceph_msg_get(req->r_request);
		ceph_con_send(&session->s_con, req->r_request);
	}

out_session:
	ceph_put_mds_session(session);
finish:
	if (err) {
		dout("__do_request early error %d\n", err);
		req->r_err = err;
		complete_request(mdsc, req);
		__unregister_request(mdsc, req);
	}
out:
	return err;
}
