tomoyo_path2_perm(const u8 operation, struct path *path1,
		      struct path *path2)
{
	int error = -ENOMEM;
	struct tomoyo_path_info buf1;
	struct tomoyo_path_info buf2;
	struct tomoyo_request_info r;
	struct tomoyo_obj_info obj = {
		.path1 = *path1,
		.path2 = *path2,
	};
	int idx;

	if (tomoyo_init_request_info(&r, NULL, tomoyo_pp2mac[operation])
	    == TOMOYO_CONFIG_DISABLED)
		return 0;
	buf1.name = NULL;
	buf2.name = NULL;
	idx = tomoyo_read_lock();
	if (!tomoyo_get_realpath(&buf1, path1) ||
	    !tomoyo_get_realpath(&buf2, path2))
		goto out;
	switch (operation) {
	case TOMOYO_TYPE_RENAME:
	case TOMOYO_TYPE_LINK:
		if (!d_is_dir(path1->dentry))
			break;

	case TOMOYO_TYPE_PIVOT_ROOT:
		tomoyo_add_slash(&buf1);
		tomoyo_add_slash(&buf2);
		break;
	}
	r.obj = &obj;
	r.param_type = TOMOYO_TYPE_PATH2_ACL;
	r.param.path2.operation = operation;
	r.param.path2.filename1 = &buf1;
	r.param.path2.filename2 = &buf2;
	do {
		tomoyo_check_acl(&r, tomoyo_check_path2_acl);
		error = tomoyo_audit_path2_log(&r);
	} while (error == TOMOYO_RETRY_REQUEST);
 out:
	kfree(buf1.name);
	kfree(buf2.name);
	tomoyo_read_unlock(idx);
	if (r.mode != TOMOYO_CONFIG_ENFORCING)
		error = 0;
	return error;
}
