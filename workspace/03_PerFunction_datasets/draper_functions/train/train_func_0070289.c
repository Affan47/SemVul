ceph_put_cap_refs(struct ceph_inode_info *ci, int had)
{
	struct inode *inode = &ci->vfs_inode;
	int last = 0, put = 0, flushsnaps = 0, wake = 0;

	spin_lock(&ci->i_ceph_lock);
	if (had & CEPH_CAP_PIN)
		--ci->i_pin_ref;
	if (had & CEPH_CAP_FILE_RD)
		if (--ci->i_rd_ref == 0)
			last++;
	if (had & CEPH_CAP_FILE_CACHE)
		if (--ci->i_rdcache_ref == 0)
			last++;
	if (had & CEPH_CAP_FILE_BUFFER) {
		if (--ci->i_wb_ref == 0) {
			last++;
			put++;
		}
		dout("put_cap_refs %p wb %d -> %d (?)\n",
		     inode, ci->i_wb_ref+1, ci->i_wb_ref);
	}
	if (had & CEPH_CAP_FILE_WR)
		if (--ci->i_wr_ref == 0) {
			last++;
			if (__ceph_have_pending_cap_snap(ci)) {
				struct ceph_cap_snap *capsnap =
					list_last_entry(&ci->i_cap_snaps,
							struct ceph_cap_snap,
							ci_item);
				capsnap->writing = 0;
				if (ceph_try_drop_cap_snap(capsnap))
					put++;
				else if (__ceph_finish_cap_snap(ci, capsnap))
					flushsnaps = 1;
				wake = 1;
			}
			if (ci->i_wrbuffer_ref_head == 0 &&
			    ci->i_dirty_caps == 0 &&
			    ci->i_flushing_caps == 0) {
				BUG_ON(!ci->i_head_snapc);
				ceph_put_snap_context(ci->i_head_snapc);
				ci->i_head_snapc = NULL;
			}

			if (!__ceph_is_any_caps(ci) && ci->i_snap_realm)
				drop_inode_snap_realm(ci);
		}
	spin_unlock(&ci->i_ceph_lock);

	dout("put_cap_refs %p had %s%s%s\n", inode, ceph_cap_string(had),
	     last ? " last" : "", put ? " put" : "");

	if (last && !flushsnaps)
		ceph_check_caps(ci, 0, NULL);
	else if (flushsnaps)
		ceph_flush_snaps(ci);
	if (wake)
		wake_up_all(&ci->i_cap_wq);
	while (put-- > 0)
		iput(inode);
}
