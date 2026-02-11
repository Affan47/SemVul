nfsproc3_rename_3_svc(RENAME3args * argp, struct svc_req * rqstp)
{
    static RENAME3res result;
    char *from;
    char *to;
    char from_obj[NFS_MAXPATHLEN];
    char to_obj[NFS_MAXPATHLEN];
    pre_op_attr pre;
    post_op_attr post;
    int res;

    PREP(from, argp->from.dir);
    pre = get_pre_cached();
    result.status =
	join(cat_name(from, argp->from.name, from_obj), exports_rw());

    cluster_lookup(from_obj, rqstp, &result.status);

    to = fh_decomp(argp->to.dir);

    if (result.status == NFS3_OK) {
	result.status =
	    join(cat_name(to, argp->to.name, to_obj),
		 exports_compat(to, rqstp));

	cluster_create(to_obj, rqstp, &result.status);

	if (result.status == NFS3_OK) {
	    change_readdir_cookie();
	    res = backend_rename(from_obj, to_obj);
	    if (res == -1)
		result.status = rename_err();
	}
    }

    post = get_post_attr(from, argp->from.dir, rqstp);


    result.RENAME3res_u.resok.fromdir_wcc.before = pre;
    result.RENAME3res_u.resok.fromdir_wcc.after = post;
    result.RENAME3res_u.resok.todir_wcc.before = get_pre_cached();
    result.RENAME3res_u.resok.todir_wcc.after = get_post_stat(to, rqstp);

    return &result;
}
