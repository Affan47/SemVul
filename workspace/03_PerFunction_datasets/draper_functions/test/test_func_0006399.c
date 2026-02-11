load_recdir(struct dentry *parent, struct dentry *child, struct nfsd_net *nn)
{
	if (child->d_name.len != HEXDIR_LEN - 1) {
		printk("nfsd4: illegal name %pd in recovery directory\n",
				child);

		return 0;
	}
	nfs4_client_to_reclaim(child->d_name.name, nn);
	return 0;
}
