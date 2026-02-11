handle_filetype(const char *fname, int flags,
			   STATBUF *statbuf, int *stated, enum filetype *ft,
			   cli_ftw_cb callback, struct cli_ftw_cbdata *data)
{
    int ret;

    *stated = get_filetype(fname, flags, flags & CLI_FTW_NEED_STAT , statbuf, ft);

    if (*stated == -1) {

	ret = callback(NULL, NULL, fname, error_stat, data);
	if (ret != CL_SUCCESS)
	    return ret;
	*ft = ft_unknown;
    } else if (*ft == ft_skipped_link || *ft == ft_skipped_special) {

	ret = callback(stated ? statbuf : NULL, NULL, fname,
		       *ft == ft_skipped_link ?
		       warning_skipped_link : warning_skipped_special, data);
	if (ret != CL_SUCCESS)
	    return ret;
    }
    return CL_SUCCESS;
}
