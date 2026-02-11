read_net_nfs(struct stats_net_nfs *st_net_nfs)
{
	FILE *fp;
	char line[256];
	unsigned int getattcnt = 0, accesscnt = 0, readcnt = 0, writecnt = 0;

	if ((fp = fopen(NET_RPC_NFS, "r")) == NULL)
		return;

	memset(st_net_nfs, 0, STATS_NET_NFS_SIZE);

	while (fgets(line, 256, fp) != NULL) {

		if (!strncmp(line, "rpc ", 4)) {
			sscanf(line + 4, "%u %u",
			       &st_net_nfs->nfs_rpccnt, &st_net_nfs->nfs_rpcretrans);
		}
		else if (!strncmp(line, "proc3 ", 6)) {
			sscanf(line + 6, "%*u %*u %u %*u %*u %u %*u %u %u",
			       &getattcnt, &accesscnt, &readcnt, &writecnt);

			st_net_nfs->nfs_getattcnt += getattcnt;
			st_net_nfs->nfs_accesscnt += accesscnt;
			st_net_nfs->nfs_readcnt   += readcnt;
			st_net_nfs->nfs_writecnt  += writecnt;
		}
		else if (!strncmp(line, "proc4 ", 6)) {
			sscanf(line + 6, "%*u %*u %u %u "
			       "%*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %u %u",
			       &readcnt, &writecnt, &accesscnt, &getattcnt);

			st_net_nfs->nfs_getattcnt += getattcnt;
			st_net_nfs->nfs_accesscnt += accesscnt;
			st_net_nfs->nfs_readcnt   += readcnt;
			st_net_nfs->nfs_writecnt  += writecnt;
		}
	}

	fclose(fp);
}
