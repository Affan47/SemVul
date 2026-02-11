qd_alloc(unsigned hash, struct gfs2_sbd *sdp, struct kqid qid)
{
	struct gfs2_quota_data *qd;
	int error;

	qd = kmem_cache_zalloc(gfs2_quotad_cachep, GFP_NOFS);
	if (!qd)
		return NULL;

	qd->qd_sbd = sdp;
	qd->qd_lockref.count = 1;
	spin_lock_init(&qd->qd_lockref.lock);
	qd->qd_id = qid;
	qd->qd_slot = -1;
	INIT_LIST_HEAD(&qd->qd_lru);
	qd->qd_hash = hash;

	error = gfs2_glock_get(sdp, qd2index(qd),
			      &gfs2_quota_glops, CREATE, &qd->qd_gl);
	if (error)
		goto fail;

	return qd;

fail:
	kmem_cache_free(gfs2_quotad_cachep, qd);
	return NULL;
}
