_destroy_fid(struct format_instance **fid)
{
	if (*fid) {
		(*fid)->fmt->ops->destroy_instance(*fid);
		*fid = NULL;
	}
}
