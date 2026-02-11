make_cover_letter(struct rev_info *rev, int use_stdout,
			      int numbered, int numbered_files,
			      struct commit *origin,
			      int nr, struct commit **list, struct commit *head)
{
	const char *committer;
	char *head_sha1;
	const char *subject_start = NULL;
	const char *body = "*** SUBJECT HERE ***\n\n*** BLURB HERE ***\n";
	const char *msg;
	const char *extra_headers = rev->extra_headers;
	struct shortlog log;
	struct strbuf sb = STRBUF_INIT;
	int i;
	const char *encoding = "utf-8";
	struct diff_options opts;
	int need_8bit_cte = 0;

	if (rev->commit_format != CMIT_FMT_EMAIL)
		die("Cover letter needs email format");

	if (!use_stdout && reopen_stdout(numbered_files ?
				NULL : "cover-letter", 0, rev->total))
		return;

	head_sha1 = sha1_to_hex(head->object.sha1);

	log_write_email_headers(rev, head_sha1, &subject_start, &extra_headers,
				&need_8bit_cte);

	committer = git_committer_info(0);

	msg = body;
	pp_user_info(NULL, CMIT_FMT_EMAIL, &sb, committer, DATE_RFC2822,
		     encoding);
	pp_title_line(CMIT_FMT_EMAIL, &msg, &sb, subject_start, extra_headers,
		      encoding, need_8bit_cte);
	pp_remainder(CMIT_FMT_EMAIL, &msg, &sb, 0);
	printf("%s\n", sb.buf);

	strbuf_release(&sb);

	shortlog_init(&log);
	log.wrap_lines = 1;
	log.wrap = 72;
	log.in1 = 2;
	log.in2 = 4;
	for (i = 0; i < nr; i++)
		shortlog_add_commit(&log, list[i]);

	shortlog_output(&log);


	if (!origin)
		return;

	memcpy(&opts, &rev->diffopt, sizeof(opts));
	opts.output_format = DIFF_FORMAT_SUMMARY | DIFF_FORMAT_DIFFSTAT;

	diff_setup_done(&opts);

	diff_tree_sha1(origin->tree->object.sha1,
		       head->tree->object.sha1,
		       "", &opts);
	diffcore_std(&opts);
	diff_flush(&opts);

	printf("\n");
}
