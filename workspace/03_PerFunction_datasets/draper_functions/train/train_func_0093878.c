merge_config_tree(struct cmd_context *cmd, struct dm_config_tree *cft,
		      struct dm_config_tree *newdata)
{
	struct dm_config_node *root = cft->root;
	struct dm_config_node *cn, *nextn, *oldn, *cn2;
	const struct dm_config_node *tn;

	for (cn = newdata->root; cn; cn = nextn) {
		nextn = cn->sib;

		if (!strcmp(cn->key, "tags"))
			continue;

		if ((tn = dm_config_find_node(cn->child, "tags"))) {
			if (!_match_host_tags(&cmd->tags, tn))
				continue;
		}
		if (!(oldn = dm_config_find_node(root, cn->key))) {
			_insert_config_node(&cft->root, cn);

			for (cn2 = cn->child; cn2; cn2 = cn2->sib) {
				if (!strcmp(cn2->key, "tags")) {
					cn->child = cn2->sib;
					continue;
				}
				if (cn2->sib && !strcmp(cn2->sib->key, "tags")) {
					cn2->sib = cn2->sib->sib;
					continue;
				}
			}
			continue;
		}
		_merge_section(oldn, cn);
	}

	return 1;
}
