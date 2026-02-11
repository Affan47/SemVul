filter_ref__cb(git_remote_head *head, void *payload)
{
	struct filter_payload *p = payload;
	int match = 0;

	if (!git_reference_is_valid_name(head->name))
		return 0;

	if (!p->found_head && strcmp(head->name, GIT_HEAD_FILE) == 0)
		p->found_head = 1;
	else if (git_remote__matching_refspec(p->remote, head->name))
			match = 1;
	else if (p->remote->download_tags == GIT_REMOTE_DOWNLOAD_TAGS_ALL &&
		 git_refspec_src_matches(p->tagspec, head->name))
			match = 1;

	if (!match)
		return 0;


	if (git_odb_exists(p->odb, &head->oid))
		head->local = 1;
	else
		p->remote->need_pack = 1;

	return git_vector_insert(&p->remote->refs, head);
}
