git_tag_list(git_strarray *tag_names, git_repository *repo)
{
	int error;
	git_vector taglist;

	if (git_vector_init(&taglist, 8, NULL) < GIT_SUCCESS)
		return GIT_ENOMEM;

	error = git_reference_listcb(repo, GIT_REF_OID|GIT_REF_PACKED, &tag_list_cb, (void *)&taglist);
	if (error < GIT_SUCCESS) {
		git_vector_free(&taglist);
		return error;
	}

	tag_names->strings = (char **)taglist.contents;
	tag_names->count = taglist.length;
	return GIT_SUCCESS;
}
