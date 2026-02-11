deep_copy_peer(struct dundi_peer *peer_dst, const struct dundi_peer *peer_src)
{
	struct permission *cur, *perm;

	memcpy(peer_dst, peer_src, sizeof(*peer_dst));

	memset(&peer_dst->permit, 0, sizeof(peer_dst->permit));
	memset(&peer_dst->include, 0, sizeof(peer_dst->permit));

	AST_LIST_TRAVERSE(&peer_src->permit, cur, list) {
		if (!(perm = ast_calloc(1, sizeof(*perm) + strlen(cur->name) + 1)))
			continue;

		perm->allow = cur->allow;
		strcpy(perm->name, cur->name);

		AST_LIST_INSERT_HEAD(&peer_dst->permit, perm, list);
	}

	AST_LIST_TRAVERSE(&peer_src->include, cur, list) {
		if (!(perm = ast_calloc(1, sizeof(*perm) + strlen(cur->name) + 1)))
			continue;

		perm->allow = cur->allow;
		strcpy(perm->name, cur->name);

		AST_LIST_INSERT_HEAD(&peer_dst->include, perm, list);
	}
}
