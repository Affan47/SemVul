nfs_umount_begin(struct super_block *sb)
{
	struct nfs_server *server;
	struct rpc_clnt *rpc;

	server = NFS_SB(sb);

	rpc = server->client_acl;
	if (!IS_ERR(rpc))
		rpc_killall_tasks(rpc);
	rpc = server->client;
	if (!IS_ERR(rpc))
		rpc_killall_tasks(rpc);
}
