ceph_mdsc_stop(struct ceph_mds_client *mdsc)
{
	dout("stop\n");
	cancel_delayed_work_sync(&mdsc->delayed_work);
	if (mdsc->mdsmap)
		ceph_mdsmap_destroy(mdsc->mdsmap);
	kfree(mdsc->sessions);
	ceph_caps_finalize(mdsc);
	ceph_pool_perm_destroy(mdsc);
}
