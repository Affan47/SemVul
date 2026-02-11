suggest_reattach(struct commit *commit, struct rev_info *revs)
{
	struct commit *c, *last = NULL;
	struct strbuf sb = STRBUF_INIT;
	int lost = 0;
	while ((c = get_revision(revs)) != NULL) {
		if (lost < ORPHAN_CUTOFF)
			describe_one_orphan(&sb, c);
		last = c;
		lost++;
	}
	if (ORPHAN_CUTOFF < lost) {
		int more = lost - ORPHAN_CUTOFF;
		if (more == 1)
			describe_one_orphan(&sb, last);
		else
			strbuf_addf(&sb, " ... and %d more.\n", more);
	}

	fprintf(stderr,
		"Warning: you are leaving %d commit%s behind, "
		"not connected to\n"
		"any of your branches:\n\n"
		"%s\n"
		"If you want to keep them by creating a new branch, "
		"this may be a good time\nto do so with:\n\n"
		" git branch new_branch_name %s\n\n",
		lost, ((1 < lost) ? "s" : ""),
		sb.buf,
		sha1_to_hex(commit->object.sha1));
	strbuf_release(&sb);
}
