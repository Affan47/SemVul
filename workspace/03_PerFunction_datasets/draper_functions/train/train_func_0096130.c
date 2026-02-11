nfs4_check_clientid_trunking(struct nfs_client *a, struct nfs_client *b)
{
	struct nfs41_server_owner *o1 = a->cl_serverowner;
	struct nfs41_server_owner *o2 = b->cl_serverowner;

	if (o1->major_id_sz != o2->major_id_sz)
		goto out_major_mismatch;
	if (memcmp(o1->major_id, o2->major_id, o1->major_id_sz) != 0)
		goto out_major_mismatch;

	dprintk("NFS: --> %s server owners match\n", __func__);
	return true;

out_major_mismatch:
	dprintk("NFS: --> %s server owner major IDs do not match\n",
		__func__);
	return false;
}
