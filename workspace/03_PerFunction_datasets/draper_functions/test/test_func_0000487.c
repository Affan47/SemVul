nfsproc3_commit_3_svc(COMMIT3args * argp, struct svc_req * rqstp)
{
    static COMMIT3res result;
    char *path;
    int res;

    PREP(path, argp->file);
    result.status = join(is_reg(), exports_rw());

    if (result.status == NFS3_OK) {
	res = fd_sync(argp->file);
	if (res != -1)
	    memcpy(result.COMMIT3res_u.resok.verf, wverf, NFS3_WRITEVERFSIZE);
	else

	    result.status = NFS3ERR_IO;
    }


    result.COMMIT3res_u.resfail.file_wcc.before = get_pre_cached();
    result.COMMIT3res_u.resfail.file_wcc.after = get_post_stat(path, rqstp);

    return &result;
}
