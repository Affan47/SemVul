do_fetch(struct transport *transport,
		    struct refspec *refs, int ref_count)
{
	struct ref *ref_map;
	struct ref *rm;
	int autotags = (transport->remote->fetch_tags == 1);
	if (transport->remote->fetch_tags == 2 && tags != TAGS_UNSET)
		tags = TAGS_SET;
	if (transport->remote->fetch_tags == -1)
		tags = TAGS_UNSET;

	if (!transport->get_refs_list || !transport->fetch)
		die("Don't know how to fetch from %s", transport->url);


	if (!append) {
		char *filename = git_path("FETCH_HEAD");
		FILE *fp = fopen(filename, "w");
		if (!fp)
			return error("cannot open %s: %s\n", filename, strerror(errno));
		fclose(fp);
	}

	ref_map = get_ref_map(transport, refs, ref_count, tags, &autotags);

	for (rm = ref_map; rm; rm = rm->next) {
		if (rm->peer_ref)
			read_ref(rm->peer_ref->name, rm->peer_ref->old_sha1);
	}

	if (tags == TAGS_DEFAULT && autotags)
		transport_set_option(transport, TRANS_OPT_FOLLOWTAGS, "1");
	if (fetch_refs(transport, ref_map)) {
		free_refs(ref_map);
		return 1;
	}
	free_refs(ref_map);


	if (tags == TAGS_DEFAULT && autotags) {
		struct ref **tail = &ref_map;
		ref_map = NULL;
		find_non_local_tags(transport, &ref_map, &tail);
		if (ref_map) {
			transport_set_option(transport, TRANS_OPT_FOLLOWTAGS, NULL);
			transport_set_option(transport, TRANS_OPT_DEPTH, "0");
			fetch_refs(transport, ref_map);
		}
		free_refs(ref_map);
	}

	return 0;
}
