v9fs_session_close(struct v9fs_session_info *v9ses)
{
	if (v9ses->clnt) {
		p9_client_destroy(v9ses->clnt);
		v9ses->clnt = NULL;
	}

#ifdef CONFIG_9P_FSCACHE
	if (v9ses->fscache) {
		v9fs_cache_session_put_cookie(v9ses);
		kfree(v9ses->cachetag);
	}
#endif
	kfree(v9ses->uname);
	kfree(v9ses->aname);

	bdi_destroy(&v9ses->bdi);

	spin_lock(&v9fs_sessionlist_lock);
	list_del(&v9ses->slist);
	spin_unlock(&v9fs_sessionlist_lock);
}
