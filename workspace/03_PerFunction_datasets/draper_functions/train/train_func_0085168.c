get_ref_map(struct transport *transport,
			       struct refspec *refs, int ref_count, int tags,
			       int *autotags)
{
	int i;
	struct ref *rm;
	struct ref *ref_map = NULL;
	struct ref **tail = &ref_map;

	const struct ref *remote_refs = transport_get_remote_refs(transport);

	if (ref_count || tags == TAGS_SET) {
		for (i = 0; i < ref_count; i++) {
			get_fetch_map(remote_refs, &refs[i], &tail, 0);
			if (refs[i].dst && refs[i].dst[0])
				*autotags = 1;
		}

		for (rm = ref_map; rm; rm = rm->next)
			rm->merge = 1;
		if (tags == TAGS_SET) {
			struct refspec refspec;
			refspec.src = "refs/tags/";
			refspec.dst = "refs/tags/";
			refspec.pattern = 1;
			refspec.force = 0;
			get_fetch_map(remote_refs, &refspec, &tail, 0);
		}
	} else {

		struct remote *remote = transport->remote;
		struct branch *branch = branch_get(NULL);
		int has_merge = branch_has_merge_config(branch);
		if (remote && (remote->fetch_refspec_nr || has_merge)) {
			for (i = 0; i < remote->fetch_refspec_nr; i++) {
				get_fetch_map(remote_refs, &remote->fetch[i], &tail, 0);
				if (remote->fetch[i].dst &&
				    remote->fetch[i].dst[0])
					*autotags = 1;
				if (!i && !has_merge && ref_map &&
				    !remote->fetch[0].pattern)
					ref_map->merge = 1;
			}


			if (has_merge &&
			    !strcmp(branch->remote_name, remote->name))
				add_merge_config(&ref_map, remote_refs, branch, &tail);
		} else {
			ref_map = get_remote_ref(remote_refs, "HEAD");
			if (!ref_map)
				die("Couldn't find remote ref HEAD");
			ref_map->merge = 1;
			tail = &ref_map->next;
		}
	}
	if (tags == TAGS_DEFAULT && *autotags)
		find_non_local_tags(transport, &ref_map, &tail);
	ref_remove_duplicates(ref_map);

	return ref_map;
}
