cld_pipe_upcall(struct rpc_pipe *pipe, struct cld_msg *cmsg)
{
	int ret;


	do {
		ret = __cld_pipe_upcall(pipe, cmsg);
	} while (ret == -EAGAIN);

	return ret;
}
