parse_tellme_more(char *line, int len, struct commit_list **list)
{
	unsigned char sha1[20];
	struct commit *c;

	if (52 <= len &&
	    !strncmp(line, "tellme-more ", 12) &&
	    !get_sha1_hex(line + 12, sha1)) {
		c = lookup_commit_reference_gently(sha1, 1);
		if (c)
			commit_list_insert(c, list);
		return 1;
	}
	return 0;
}
