rpc_pipefs_event(struct notifier_block *nb, unsigned long event, void *ptr)
{
	struct super_block *sb = ptr;
	struct net *net = sb->s_fs_info;
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	struct cld_net *cn = nn->cld_net;
	struct dentry *dentry;
	int ret = 0;

	if (!try_module_get(THIS_MODULE))
		return 0;

	if (!cn) {
		module_put(THIS_MODULE);
		return 0;
	}

	switch (event) {
	case RPC_PIPEFS_MOUNT:
		dentry = nfsd4_cld_register_sb(sb, cn->cn_pipe);
		if (IS_ERR(dentry)) {
			ret = PTR_ERR(dentry);
			break;
		}
		cn->cn_pipe->dentry = dentry;
		break;
	case RPC_PIPEFS_UMOUNT:
		if (cn->cn_pipe->dentry)
			nfsd4_cld_unregister_sb(cn->cn_pipe);
		break;
	default:
		ret = -ENOTSUPP;
		break;
	}
	module_put(THIS_MODULE);
	return ret;
}
