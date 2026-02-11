ceph_dentry_lru_touch(struct dentry *dn)
{
	struct ceph_dentry_info *di = ceph_dentry(dn);
	struct ceph_mds_client *mdsc;

	dout("dentry_lru_touch %p %p '%pd' (offset %lld)\n", di, dn, dn,
	     di->offset);
	mdsc = ceph_sb_to_client(dn->d_sb)->mdsc;
	spin_lock(&mdsc->dentry_lru_lock);
	list_move_tail(&di->lru, &mdsc->dentry_lru);
	spin_unlock(&mdsc->dentry_lru_lock);
}
