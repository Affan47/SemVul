nfs4_put_deviceid_node(struct nfs4_deviceid_node *d)
{
	if (test_bit(NFS_DEVICEID_NOCACHE, &d->flags)) {
		if (atomic_add_unless(&d->ref, -1, 2))
			return false;
		nfs4_delete_deviceid(d->ld, d->nfs_client, &d->deviceid);
	}
	if (!atomic_dec_and_test(&d->ref))
		return false;
	d->ld->free_deviceid_node(d);
	return true;
}
