gfs2_rs_delete(struct gfs2_inode *ip, atomic_t *wcount)
{
	down_write(&ip->i_rw_mutex);
	if (ip->i_res && ((wcount == NULL) || (atomic_read(wcount) <= 1))) {
		gfs2_rs_deltree(ip->i_res);
		BUG_ON(ip->i_res->rs_free);
		kmem_cache_free(gfs2_rsrv_cachep, ip->i_res);
		ip->i_res = NULL;
	}
	up_write(&ip->i_rw_mutex);
}
