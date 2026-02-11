find_default_branch(struct cgit_repo *repo)
{
	struct refmatch info;
	char *ref;

	info.req_ref = repo->defbranch;
	info.first_ref = NULL;
	info.match = 0;
	for_each_branch_ref(find_current_ref, &info);
	if (info.match)
		ref = info.req_ref;
	else
		ref = info.first_ref;
	if (ref)
		ref = xstrdup(ref);
	return ref;
}
