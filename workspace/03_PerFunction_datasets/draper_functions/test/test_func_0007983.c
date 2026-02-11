match_refs(struct ref *src, struct ref *dst, struct ref ***dst_tail,
	       int nr_refspec, char **refspec, int all)
{
	struct refspec *rs =
		parse_ref_spec(nr_refspec, (const char **) refspec);

	if (match_explicit_refs(src, dst, dst_tail, rs, nr_refspec))
		return -1;


	for ( ; src; src = src->next) {
		struct ref *dst_peer;
		const struct refspec *pat = NULL;
		char *dst_name;
		if (src->peer_ref)
			continue;
		if (nr_refspec) {
			pat = check_pattern_match(rs, nr_refspec, src);
			if (!pat)
				continue;
		}

		if (pat) {
			const char *dst_side = pat->dst ? pat->dst : pat->src;
			dst_name = xmalloc(strlen(dst_side) +
					   strlen(src->name) -
					   strlen(pat->src) + 2);
			strcpy(dst_name, dst_side);
			strcat(dst_name, src->name + strlen(pat->src));
		} else
			dst_name = xstrdup(src->name);
		dst_peer = find_ref_by_name(dst, dst_name);
		if (dst_peer && dst_peer->peer_ref)

			goto free_name;
		if (!dst_peer && !nr_refspec && !all)


			goto free_name;
		if (!dst_peer) {

			dst_peer = make_dst(dst_name, dst_tail);
			hashcpy(dst_peer->new_sha1, src->new_sha1);
		}
		dst_peer->peer_ref = src;
	free_name:
		free(dst_name);
	}
	return 0;
}
