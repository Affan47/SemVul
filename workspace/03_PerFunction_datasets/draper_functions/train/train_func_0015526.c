ceph_put_wrbuffer_cap_refs(struct ceph_inode_info *ci, int nr,
				struct ceph_snap_context *snapc)
{
	struct inode *inode = &ci->vfs_inode;
	int last = 0;
	int complete_capsnap = 0;
	int drop_capsnap = 0;
	int found = 0;
	struct ceph_cap_snap *capsnap = NULL;

	spin_lock(&ci->i_ceph_lock);
	ci->i_wrbuffer_ref -= nr;
	last = !ci->i_wrbuffer_ref;

	if (ci->i_head_snapc == snapc) {
		ci->i_wrbuffer_ref_head -= nr;
		if (ci->i_wrbuffer_ref_head == 0 &&
		    ci->i_wr_ref == 0 &&
		    ci->i_dirty_caps == 0 &&
		    ci->i_flushing_caps == 0) {
			BUG_ON(!ci->i_head_snapc);
			ceph_put_snap_context(ci->i_head_snapc);
			ci->i_head_snapc = NULL;
		}
		dout("put_wrbuffer_cap_refs on %p head %d/%d -> %d/%d %s\n",
		     inode,
		     ci->i_wrbuffer_ref+nr, ci->i_wrbuffer_ref_head+nr,
		     ci->i_wrbuffer_ref, ci->i_wrbuffer_ref_head,
		     last ? " LAST" : "");
	} else {
		list_for_each_entry(capsnap, &ci->i_cap_snaps, ci_item) {
			if (capsnap->context == snapc) {
				found = 1;
				break;
			}
		}
		BUG_ON(!found);
		capsnap->dirty_pages -= nr;
		if (capsnap->dirty_pages == 0) {
			complete_capsnap = 1;
			drop_capsnap = ceph_try_drop_cap_snap(capsnap);
		}
		dout("put_wrbuffer_cap_refs on %p cap_snap %p "
		     " snap %lld %d/%d -> %d/%d %s%s\n",
		     inode, capsnap, capsnap->context->seq,
		     ci->i_wrbuffer_ref+nr, capsnap->dirty_pages + nr,
		     ci->i_wrbuffer_ref, capsnap->dirty_pages,
		     last ? " (wrbuffer last)" : "",
		     complete_capsnap ? " (complete capsnap)" : "");
	}

	spin_unlock(&ci->i_ceph_lock);

	if (last) {
		ceph_check_caps(ci, CHECK_CAPS_AUTHONLY, NULL);
		iput(inode);
	} else if (complete_capsnap) {
		ceph_flush_snaps(ci);
		wake_up_all(&ci->i_cap_wq);
	}
	if (drop_capsnap)
		iput(inode);
}
