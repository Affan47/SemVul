print_ematch_list(FILE *fd, struct tcf_ematch_tree_hdr *hdr,
			     struct rtattr *rta)
{
	int err = -1;
	struct rtattr **tb;

	tb = malloc((hdr->nmatches + 1) * sizeof(struct rtattr *));
	if (tb == NULL)
		return -1;

	if (hdr->nmatches > 0) {
		if (parse_rtattr_nested(tb, hdr->nmatches, rta) < 0)
			goto errout;

		fprintf(fd, "\n  ");
		if (print_ematch_seq(fd, tb, 1, 1) < 0)
			goto errout;
	}

	err = 0;
errout:
	free(tb);
	return err;
}
