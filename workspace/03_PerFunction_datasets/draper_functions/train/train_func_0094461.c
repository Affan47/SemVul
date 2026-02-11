knet_close(knetFile *fp)
{
	if (fp == 0) return 0;
	if (fp->ctrl_fd != -1) netclose(fp->ctrl_fd);
	if (fp->fd != -1) {


		if (fp->type == KNF_TYPE_LOCAL) close(fp->fd);
		else netclose(fp->fd);
	}
	free(fp->host); free(fp->port);
	free(fp->response); free(fp->retr);
	free(fp->path); free(fp->http_host);
	free(fp);
	return 0;
}
