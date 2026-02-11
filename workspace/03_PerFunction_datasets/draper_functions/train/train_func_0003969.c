__rep_remove_nimdbs(env)
	ENV *env;
{
	FILE_LIST_CTX context;
	int ret;

	if ((ret = __rep_init_file_list_context(env,
	    DB_REPVERSION, 0, 0, &context)) != 0)
		return (ret);


	if ((ret = __rep_walk_dir(env, NULL, NULL, &context)) != 0)
		goto out;

	if ((ret = __rep_closefiles(env)) != 0)
		goto out;

	ret = __rep_walk_filelist(env, context.version, context.buf,
	    context.size, context.count, __rep_remove_file, NULL);

out:
	__os_free(env, context.buf);
	return (ret);
}
