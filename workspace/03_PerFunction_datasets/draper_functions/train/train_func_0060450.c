init_cifs(void)
{
	int rc = 0;
	cifs_proc_init();
	INIT_LIST_HEAD(&cifs_tcp_ses_list);
#ifdef CONFIG_CIFS_DNOTIFY_EXPERIMENTAL
	INIT_LIST_HEAD(&GlobalDnotifyReqList);
	INIT_LIST_HEAD(&GlobalDnotifyRsp_Q);
#endif


	atomic_set(&sesInfoAllocCount, 0);
	atomic_set(&tconInfoAllocCount, 0);
	atomic_set(&tcpSesAllocCount, 0);
	atomic_set(&tcpSesReconnectCount, 0);
	atomic_set(&tconInfoReconnectCount, 0);

	atomic_set(&bufAllocCount, 0);
	atomic_set(&smBufAllocCount, 0);
#ifdef CONFIG_CIFS_STATS2
	atomic_set(&totBufAllocCount, 0);
	atomic_set(&totSmBufAllocCount, 0);
#endif

	atomic_set(&midCount, 0);
	GlobalCurrentXid = 0;
	GlobalTotalActiveXid = 0;
	GlobalMaxActiveXid = 0;
	spin_lock_init(&cifs_tcp_ses_lock);
	spin_lock_init(&GlobalMid_Lock);

	if (cifs_max_pending < 2) {
		cifs_max_pending = 2;
		cifs_dbg(FYI, "cifs_max_pending set to min of 2\n");
	} else if (cifs_max_pending > CIFS_MAX_REQ) {
		cifs_max_pending = CIFS_MAX_REQ;
		cifs_dbg(FYI, "cifs_max_pending set to max of %u\n",
			 CIFS_MAX_REQ);
	}

	cifsiod_wq = alloc_workqueue("cifsiod", WQ_FREEZABLE|WQ_MEM_RECLAIM, 0);
	if (!cifsiod_wq) {
		rc = -ENOMEM;
		goto out_clean_proc;
	}

	rc = cifs_fscache_register();
	if (rc)
		goto out_destroy_wq;

	rc = cifs_init_inodecache();
	if (rc)
		goto out_unreg_fscache;

	rc = cifs_init_mids();
	if (rc)
		goto out_destroy_inodecache;

	rc = cifs_init_request_bufs();
	if (rc)
		goto out_destroy_mids;

#ifdef CONFIG_CIFS_UPCALL
	rc = register_key_type(&cifs_spnego_key_type);
	if (rc)
		goto out_destroy_request_bufs;
#endif

#ifdef CONFIG_CIFS_ACL
	rc = init_cifs_idmap();
	if (rc)
		goto out_register_key_type;
#endif

	rc = register_filesystem(&cifs_fs_type);
	if (rc)
		goto out_init_cifs_idmap;

	return 0;

out_init_cifs_idmap:
#ifdef CONFIG_CIFS_ACL
	exit_cifs_idmap();
out_register_key_type:
#endif
#ifdef CONFIG_CIFS_UPCALL
	unregister_key_type(&cifs_spnego_key_type);
out_destroy_request_bufs:
#endif
	cifs_destroy_request_bufs();
out_destroy_mids:
	cifs_destroy_mids();
out_destroy_inodecache:
	cifs_destroy_inodecache();
out_unreg_fscache:
	cifs_fscache_unregister();
out_destroy_wq:
	destroy_workqueue(cifsiod_wq);
out_clean_proc:
	cifs_proc_clean();
	return rc;
}
