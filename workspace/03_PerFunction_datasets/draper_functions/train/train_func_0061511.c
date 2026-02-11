ceph_mdsc_close_sessions(struct ceph_mds_client *mdsc)
{
	struct ceph_options *opts = mdsc->fsc->client->options;
	struct ceph_mds_session *session;
	int i;

	dout("close_sessions\n");


	mutex_lock(&mdsc->mutex);
	for (i = 0; i < mdsc->max_sessions; i++) {
		session = __ceph_lookup_mds_session(mdsc, i);
		if (!session)
			continue;
		mutex_unlock(&mdsc->mutex);
		mutex_lock(&session->s_mutex);
		__close_session(mdsc, session);
		mutex_unlock(&session->s_mutex);
		ceph_put_mds_session(session);
		mutex_lock(&mdsc->mutex);
	}
	mutex_unlock(&mdsc->mutex);

	dout("waiting for sessions to close\n");
	wait_event_timeout(mdsc->session_close_wq, done_closing_sessions(mdsc),
			   ceph_timeout_jiffies(opts->mount_timeout));


	mutex_lock(&mdsc->mutex);
	for (i = 0; i < mdsc->max_sessions; i++) {
		if (mdsc->sessions[i]) {
			session = get_session(mdsc->sessions[i]);
			__unregister_session(mdsc, session);
			mutex_unlock(&mdsc->mutex);
			mutex_lock(&session->s_mutex);
			remove_session_caps(session);
			mutex_unlock(&session->s_mutex);
			ceph_put_mds_session(session);
			mutex_lock(&mdsc->mutex);
		}
	}
	WARN_ON(!list_empty(&mdsc->cap_delay_list));
	mutex_unlock(&mdsc->mutex);

	ceph_cleanup_empty_realms(mdsc);

	cancel_delayed_work_sync(&mdsc->delayed_work);

	dout("stopped\n");
}
