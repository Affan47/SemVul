mount_call(uint32_t proc, uint32_t version,
		      const char *path, struct client *clnt)
{
	struct mount_call *mnt_call = NULL;
	size_t path_len, call_len;
	struct rpc rpc;
	int ret = 0;

	path_len = strlen(path);
	call_len = sizeof(*mnt_call) + pad_len(path_len);

	mnt_call = malloc(call_len);
	if (mnt_call == NULL) {
		perror("malloc");
		goto bail;
	}

	memset(mnt_call, 0, sizeof(*mnt_call));

	mnt_call->rpc.program = htonl(NFS_MNT_PROGRAM);
	mnt_call->rpc.prog_vers = htonl(version);
	mnt_call->rpc.proc = htonl(proc);
	mnt_call->path_len = htonl(path_len);
	memcpy(mnt_call->path, path, path_len);

	rpc.call = (struct rpc_call *)mnt_call;
	rpc.call_len = call_len;
	rpc.reply = (struct rpc_reply *)&mnt_reply;
	rpc.reply_len = sizeof(mnt_reply);

	if (rpc_call(clnt, &rpc) < 0)
		goto bail;

	if (proc != MNTPROC_MNT)
		goto done;

	if (rpc.reply_len < MNT_REPLY_MINSIZE) {
		fprintf(stderr, "incomplete reply: %zu < %zu\n",
			rpc.reply_len, MNT_REPLY_MINSIZE);
		goto bail;
	}

	if (mnt_reply.status != 0) {
		fprintf(stderr, "mount call failed - server replied: %s.\n",
			strerror(ntohl(mnt_reply.status)));
		goto bail;
	}

	goto done;

bail:
	ret = -1;

done:
	if (mnt_call)
		free(mnt_call);

	return ret;
}
