get_expanded_map(const struct ref *remote_refs,
				    const struct refspec *refspec)
{
	const struct ref *ref;
	struct ref *ret = NULL;
	struct ref **tail = &ret;

	int remote_prefix_len = strlen(refspec->src);
	int local_prefix_len = strlen(refspec->dst);

	for (ref = remote_refs; ref; ref = ref->next) {
		if (strchr(ref->name, '^'))
			continue;
		if (!prefixcmp(ref->name, refspec->src)) {
			const char *match;
			struct ref *cpy = copy_ref(ref);
			match = ref->name + remote_prefix_len;

			cpy->peer_ref = alloc_ref(local_prefix_len +
						  strlen(match) + 1);
			sprintf(cpy->peer_ref->name, "%s%s",
				refspec->dst, match);
			if (refspec->force)
				cpy->peer_ref->force = 1;
			*tail = cpy;
			tail = &cpy->next;
		}
	}

	return ret;
}
