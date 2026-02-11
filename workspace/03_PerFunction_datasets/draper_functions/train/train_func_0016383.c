git_describe_result_free(git_describe_result *result)
{
	if (result == NULL)
		return;

	if (result->name) {
		git_tag_free(result->name->tag);
		git__free(result->name->path);
		git__free(result->name);
	}

	if (result->tag) {
		git_tag_free(result->tag->name->tag);
		git__free(result->tag->name->path);
		git__free(result->tag->name);
		git__free(result->tag);
	}

	git__free(result);
}
